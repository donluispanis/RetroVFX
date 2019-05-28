#include "Imp_Includes.h"
#include "../../Utils/ColourStampGradients.h"
#include "../../Utils/TurbulencePath.h"

void FinalDemo::InitEnding()
{
    start = {-200.f, height / 2 - 1.f};
    end = {width + 200.f, height / 2 - 1.f};

    cosineTable = Fast::GenerateCosineTable(mathTableSize);

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

void FinalDemo::CloseEnding()
{
    Fast::DeleteMathTable(cosineTable);
    delete[] tunnelColourMap;
}

void FinalDemo::UpdateEnding(float deltaTime)
{
    static float accumulator = -6.f;
    static float opacity = 0.f;
    static int auxX, auxY;

    if (Fast::Abs(start.X - end.X) > 3.f)
    {
        RenderLine(start.X, start.Y, end.X, end.Y, Pixel(255), 4);

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

        RenderLine(start.X, start.Y, end.X, end.Y, Pixel(0), 4);
    }
    else
    {
        static const int halfWidth = width / 2;

        if (eraseText)
        {
            RenderText("Developed by", 280 + auxX, 235 + auxY, 10, Pixel(0));
            RenderText("Luis gonzalez aracil", 40 + auxX, 335 + auxY, 10, Pixel(0));
            RenderText("(c) 2018", 400 + auxX, 435 + auxY, 10, Pixel(0));
        }

        if (transitionAdvance < halfWidth + 5)
        {
            ClearScreen(halfWidth - transitionAdvance, 0, halfWidth, height, Pixel(0));
            ClearScreen(halfWidth, 0, halfWidth + transitionAdvance, height, Pixel(0));
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

                if(radiusVelocity <= 0.f)
                {
                    radiusVelocity = 0.001f;
                }
            }
        }
    }
    UpdateCircleQueue(deltaTime);

    if (accumulatedTime >= START_ENDING + 25.f)
    {
        eraseText = true;

        opacity += 0.5 * deltaTime;
        if (opacity > 1.f)
        {
            opacity = 1.f;
        }

        auxX = tunnelCenter.X * 0.2f;
        auxY = tunnelCenter.Y * 0.2f;

        RenderText("Developed by", 280 + auxX, 235 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
        RenderText("Luis gonzalez aracil", 40 + auxX, 335 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
        RenderText("(c) 2018", 400 + auxX, 435 + auxY, 10, Pixel(255) * opacity * globalEndingOpacity);
    }

    if(accumulatedTime > START_ENDING + 35.f)
    {
        globalEndingOpacity -= deltaTime * 0.25;
        
        if(globalEndingOpacity < 0.f)
        {
            globalEndingOpacity = 0.f;
        }
    }
}

void FinalDemo::AddCircle()
{
    circles.push_front(Circle{defaultCircle.x + int(tunnelCenter.X - initialTunnelCenter.X),
                              defaultCircle.y + int(tunnelCenter.Y - initialTunnelCenter.Y),
                              defaultCircle.radius,
                              defaultCircle.rotation,
                              tunnelColourMap[tunnelCurrentColour % tunnelColourMapSize]});
}

void FinalDemo::UpdateCircleQueue(float deltaTime)
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

void FinalDemo::PopulateCircleQueue()
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

void FinalDemo::DrawCircle(const Circle &c)
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
            RenderDot(x, y, finalColour, dotSize);
        }
    }
}

float FinalDemo::CalculateOpacity(const float radius)
{
    float opacity = 1.f;
    float fadeIn = 1.3, fadeOut = 0.7;

    if (radius < defaultCircle.radius * fadeIn)
    {
        opacity = 1 / (defaultCircle.radius * fadeIn - radius + 1); //Starts at 0 and goes up to 1

        if(defaultCircle.radius * fadeIn - radius + 1 == 0.f)
        {
            opacity = 0.f;
        }
    }

    if (radius > maxCircleRadius * fadeOut)
    {
        opacity = (maxCircleRadius - radius) / (maxCircleRadius - maxCircleRadius * fadeOut); //Starts at 1 and goes down to 0

        if(maxCircleRadius - maxCircleRadius * fadeOut == 0.f)
        {
            opacity = 0.f;
        }
    }

    if (opacity < 0.f)
    {
        opacity *= -1.f;
    }

    return opacity;
}

void FinalDemo::UpdateCircle(Circle &c, float deltaTime)
{
    c.radius += c.radius * deltaTime * radiusVelocity;
    c.rotation += deltaTime * rotationVelocity * 2;
}

void FinalDemo::EraseCircle(const Circle &circle)
{
    Circle c = circle;
    c.colour = Pixel();
    DrawCircle(c);
}