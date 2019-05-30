#include "Imp_Ending.h"
#include "../../Utils/ColourStampGradients.h"
#include "../../Utils/TurbulencePath.h"
#include "../../Utils/Fast.h"
#include "../FinalDemo.h"
#include <cmath>

void Imp_Ending::InitEnding(int width, int height, FinalDemo* engine, float* cosTable, float* sinTable)
{
    this->width = width;
    this->height = height;
    this->engine = engine;
    this->cosineTable = cosTable;
    this->sineTable = sinTable;

    start = {-200.f, height / 2 - 1.f};
    end = {width + 200.f, height / 2 - 1.f};

    maxCircleRadius = height;
    circleCount = 20;
    dotSize = 4;
    defaultCircle = Circle{width / 2.f, height / 2.f, 20, 0, Pixel()};

    radiusVelocity = 1;
    defaultRotationVelocity = 20;
    rotationVelocity = defaultRotationVelocity;

    circlesGapDistance = 2;
    pointsPerCircle = 65;

    tunnelColourMapSize = 50;
    tunnelColourMap = new Pixel[tunnelColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::RAINBOW, tunnelColourMap, tunnelColourMapSize);
    tunnelCurrentColour = 0;

    turbulencePath = new TurbulencePath(sineTable, cosineTable, mathTableSize);
    turbulencePath->CreateTurbulencePath(10, height / 2, 4);
    turbulencePath->UpdateTurbulencePath(100, tunnelCenter.X, tunnelCenter.Y);
    initialTunnelCenter = tunnelCenter;

    AddCircle();
}

void Imp_Ending::CloseEnding()
{
    delete[] tunnelColourMap;
}

void Imp_Ending::UpdateEnding(float deltaTime, float accumulatedTime, float startTime, bool& tunnelBeat)
{
    static float accumulator = -6.f;
    static float opacity = 0.f;
    static int auxX, auxY;

    if (start.X < end.X)
    {
        engine->RenderLine(start.X, start.Y, end.X, end.Y, Pixel(255), 4);

        static float rotation = 0.f;
        rotation += deltaTime * Fast::PI * 0.00025;

        start = start - Point2D(width / 2, height / 2);
        end = end - Point2D(width / 2, height / 2);
        start.X = start.X * cos(rotation) - start.Y * sin(rotation);
        start.Y = start.Y * cos(rotation) + start.X * sin(rotation);
        end.X = end.X * cos(rotation) - end.Y * sin(rotation);
        end.Y = end.Y * cos(rotation) + end.X * sin(rotation);
        start = start + Point2D(width / 2, height / 2);
        end = end + Point2D(width / 2, height / 2);

        engine->RenderLine(start.X, start.Y, end.X, end.Y, Pixel(0), 4);
    }
    else
    {
        static const int halfWidth = width / 2;

        if (eraseText)
        {
            engine->RenderText("Developed by", 280 + auxX, 235 + auxY, 10, Pixel(0));
            engine->RenderText("Luis gonzalez aracil", 40 + auxX, 335 + auxY, 10, Pixel(0));
            engine->RenderText("(c) 2018", 400 + auxX, 435 + auxY, 10, Pixel(0));
        }

        if (transitionAdvance < halfWidth + 5)
        {
            engine->ClearScreen(halfWidth - transitionAdvance, 0, halfWidth, height, Pixel(0));
            engine->ClearScreen(halfWidth, 0, halfWidth + transitionAdvance, height, Pixel(0));
            transitionAdvance += 128 * deltaTime;
            drawTunnel = true;
        }
        else
        {
            turbulencePath->UpdateTurbulencePath(deltaTime, tunnelCenter.X, tunnelCenter.Y);
            initialTunnelCenter.X *= 0.999;
            initialTunnelCenter.Y *= 0.999;

            accumulator += deltaTime;

            if (accumulator >= 1.f)
            {
                tunnelBeat = true;
                radiusVelocity = 2.f;
                accumulator = 0.f;
            }
            if (radiusVelocity > 1.f)
            {
                radiusVelocity -= deltaTime;
            }
        }
    }

    UpdateCircleQueue(deltaTime);

    if (accumulatedTime >= startTime + 25.f)
    {
        eraseText = true;

        opacity += 0.5 * deltaTime;
        if (opacity > 1.f)
        {
            opacity = 1.f;
        }

        auxX = tunnelCenter.X * 0.2f;
        auxY = tunnelCenter.Y * 0.2f;

        engine->RenderText("Developed by", 280 + auxX, 235 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
        engine->RenderText("Luis gonzalez aracil", 40 + auxX, 335 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
        engine->RenderText("(c) 2018", 400 + auxX, 435 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
    }

    if(accumulatedTime > startTime + 35.f)
    {
        globalEndingOpacity -= deltaTime * 0.25;
        
        if(globalEndingOpacity < 0.f)
        {
            globalEndingOpacity = 0.f;
        }
    }
}

void Imp_Ending::AddCircle()
{
    circles.push_front(Circle{defaultCircle.x + int(tunnelCenter.X - initialTunnelCenter.X),
                              defaultCircle.y + int(tunnelCenter.Y - initialTunnelCenter.Y),
                              defaultCircle.radius,
                              defaultCircle.rotation,
                              tunnelColourMap[tunnelCurrentColour % tunnelColourMapSize]});
}

void Imp_Ending::UpdateCircleQueue(float deltaTime)
{
    for (auto c : circles)
    {
        EraseCircle(c);
    }

    PopulateCircleQueue();

    for (auto &c : circles)
    {
        UpdateCircle(c, deltaTime);
        DrawCircle(c);
    }
}

void Imp_Ending::PopulateCircleQueue()
{
    if (circles.front().radius > defaultCircle.radius + (defaultCircle.radius * circlesGapDistance) / circleCount)
    {
        tunnelCurrentColour++;
        AddCircle();
    }
    if (circles.back().radius > maxCircleRadius)
    {
        circles.pop_back();
    }
}

void Imp_Ending::DrawCircle(const Circle &c)
{
    const float increment = (2 * Fast::PI) / float(pointsPerCircle);
    const int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;

    for (float angle = 0, n = 2 * Fast::PI; angle < n; angle += increment)
    {
        x = cosineTable[int(angle * indexFactor + c.rotation) % mathTableSize] * c.radius + c.x;
        y = sineTable[int(angle * indexFactor + c.rotation) % mathTableSize] * c.radius + c.y;

        Pixel finalColour = c.colour * CalculateOpacity(c.radius) * globalEndingOpacity;

        if (drawTunnel && x > (width / 2 - transitionAdvance) && x < (width / 2 + transitionAdvance - dotSize))
        {
            engine->RenderDot(x, y, finalColour, dotSize);
        }
    }
}

float Imp_Ending::CalculateOpacity(const float radius)
{
    float opacity = 1.f;
    float fadeIn = 1.3, fadeOut = 0.7;

    if (radius < defaultCircle.radius * fadeIn)
    {
        opacity = 1 / (defaultCircle.radius * fadeIn - radius + 1); //Starts at 0 and goes up to 1
    }

    if (radius > maxCircleRadius * fadeOut)
    {
        opacity = (maxCircleRadius - radius) / (maxCircleRadius - maxCircleRadius * fadeOut); //Starts at 1 and goes down to 0
    }

    if (opacity < 0.f)
    {
        opacity *= -1.f;
    }

    return opacity;
}

void Imp_Ending::UpdateCircle(Circle &c, float deltaTime)
{
    c.radius += c.radius * deltaTime * radiusVelocity;
    c.rotation += deltaTime * rotationVelocity * 2;
}

void Imp_Ending::EraseCircle(const Circle &circle)
{
    Circle c = circle;
    c.colour = Pixel();
    DrawCircle(c);
}