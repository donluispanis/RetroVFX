#include "DotTunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>
#include <vector>

struct TurbulencePath
{
    int radius;
    int phase;
    int direction;
    float advance;
};

bool DotTunnelDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);

    circleCount = 20;
    defaultCircle.x = width / 2;
    defaultCircle.y = height / 2;
    defaultCircle.radius = 20;
    defaultCircle.rotation = 0;
    defaultCircle.density = 0.05;
    defaultCircle.colour = Pixel(0, 0, 0);

    pathX = 0.f;
    pathY = 0.f;
    pathRadius = height / 2;
    pathComplexity = 4;
    pathVelocity = 10;

    pathCirclesDistance = 1;

    InitCircleQueue();

    return true;
}

void DotTunnelDemo::InitCircleQueue()
{
    UpdateTunnelPath(100);

    circles.push_back(Circle{defaultCircle.x + pathX * pathRadius,
                             defaultCircle.y + pathY * pathRadius,
                             defaultCircle.radius,
                             defaultCircle.rotation,
                             defaultCircle.density,
                             Pixel(0)});
}

bool DotTunnelDemo::Update(float deltaTime)
{
    UpdateCircleQueue(deltaTime);
    UpdateTunnelPath(deltaTime);

    RenderText("DotTunnel effect.", 5, 5, 2, Pixel(255));
    return true;
}

void DotTunnelDemo::UpdateCircleQueue(float deltaTime)
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

void DotTunnelDemo::PopulateCircleQueue()
{
    if (circles[0].radius > defaultCircle.radius + (defaultCircle.radius * pathCirclesDistance) / circleCount)
    {
        circles.push_front({defaultCircle.x + pathX * pathRadius,
                            defaultCircle.y + pathY * pathRadius,
                            defaultCircle.radius,
                            defaultCircle.rotation,
                            defaultCircle.density,
                            {Pixel(255)}});
    }

    if (circles[circles.size() - 1].radius > height)
    {
        circles.pop_back();
    }
}

void DotTunnelDemo::DrawCircle(const Circle &c)
{
    float increment = 1 / (float)(c.radius * c.density);
    int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {
        x = sineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.x;
        y = cosineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.y;

        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
        {
            continue;
        }

        pixels[y * width + x] = c.colour;
        pixels[y * width + x - 1] = c.colour;
        pixels[(y + 1) * width + x] = c.colour;
        pixels[(y + 1) * width + -1] = c.colour;
    }
}

void DotTunnelDemo::UpdateCircle(Circle &c, float deltaTime)
{
    c.radius += c.radius * deltaTime * 0.3;
    
    int i = 255 * (c.radius / float(defaultCircle.radius * 5));

    if(i < 255)
    {
        c.colour = Pixel(i);
    }
}

void DotTunnelDemo::EraseCircle(const Circle &circle)
{
    Circle c = circle;
    c.colour = Pixel();
    DrawCircle(c);
}

void DotTunnelDemo::UpdateTunnelPath(float deltaTime)
{
    static std::vector<TurbulencePath> turbulencePaths;

    pathX = 0.f;
    pathY = 0.f;

    for (int i = 0; i < pathComplexity; i++)
    {
        if ((int)turbulencePaths.size() < pathComplexity)
        {
            turbulencePaths.push_back(TurbulencePath{
                height / (i + 2),
                (int)Fast::Rand() % mathTableSize,
                i % 2 == 0 ? 1 : -1,
                0});
        }

        TurbulencePath &tP = turbulencePaths[i];
        tP.advance += deltaTime * 0.1;
        int waveAmplitude = (tP.advance * tP.radius * pathVelocity) / float(i + 2);
        pathX += cosineTable[int(waveAmplitude + tP.phase) % mathTableSize];
        pathY += sineTable[int(waveAmplitude + tP.phase) % mathTableSize];
    }

    pathX /= (float)pathComplexity;
    pathY /= (float)pathComplexity;
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}