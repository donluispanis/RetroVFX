#include "DotTunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>
#include <cmath>

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
    defaultCircle.radius = 50;
    defaultCircle.rotation = 0;
    defaultCircle.density = 0.05;
    defaultCircle.colour = Pixel{255,0,0};

    InitCircleQueue();

    return true;
}

void DotTunnelDemo::InitCircleQueue()
{
    for (int i = 0; i < circleCount; i++)
    {
        circles.push_back(Circle{defaultCircle.x, defaultCircle.y, (defaultCircle.radius * circleCount) / (circleCount - i + 1),
                                 defaultCircle.rotation, defaultCircle.density});
    }
}

bool DotTunnelDemo::Update(float deltaTime)
{
    UpdateCircleQueue();

    RenderText("DotTunnel effect.", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void DotTunnelDemo::UpdateCircleQueue()
{
    for (auto c : circles)
    {
        EraseCircle(c);
    }

    if (circles[0].radius > defaultCircle.radius + defaultCircle.radius / circleCount)
    {
        circles.push_front(defaultCircle);
    }
    if (circles[circles.size() - 1].radius > height)
    {
        circles.pop_back();
    }

    for (auto& c : circles)
    {
        UpdateCircle(c);
    }

    for (auto c : circles)
    {
        DrawCircle(c);
    }
}

void DotTunnelDemo::DrawCircle(const Circle &c)
{
    float increment = 1 / (float)(c.radius * c.density);
    int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;
    static float inc = 0;
    inc += windowManager->GetDeltaTime() * 0.005;

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {
        x = sin(i + inc) * c.radius + c.x;
        y = cos(i - inc) * c.radius + c.y;

        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
        {
            continue;
        }

        pixels[y * width + x] = c.colour;
    }
}

void DotTunnelDemo::UpdateCircle(Circle &c)
{
    c.radius += c.radius * windowManager->GetDeltaTime() * 0.1;
    c.rotation += c.radius * windowManager->GetDeltaTime() * 0.1;
    c.colour.B += 1;
}

void DotTunnelDemo::EraseCircle(const Circle &circle)
{
    Circle c = circle;
    c.colour = Pixel();
    DrawCircle(c);
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}