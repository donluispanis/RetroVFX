#include "DotTunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>

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

    if (circles[circles.size() - 1].radius > defaultCircle.radius * circles.size() / 2)
    {
        circles.pop_back();
        circles.push_front(defaultCircle);
    }

    for (auto& c : circles)
    {
        UpdateCircle(c);
    }

    for (auto c : circles)
    {
        DrawCircle(c, Pixel{255, 255, 255});
    }
}

void DotTunnelDemo::DrawCircle(const Circle &c, const Pixel &colour)
{
    float increment = 1 / (float)(c.radius * c.density);
    int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {
        x = sineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.x;
        y = sineTable[int(i * indexFactor + c.rotation + mathTableSize / 4) % mathTableSize] * c.radius + c.y;

        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
        {
            continue;
        }

        pixels[y * width + x] = colour;
    }
}

void DotTunnelDemo::UpdateCircle(Circle &c)
{
    c.radius += c.radius * windowManager->GetDeltaTime() * 0.1;
}

void DotTunnelDemo::EraseCircle(const Circle &circle)
{
    DrawCircle(circle, Pixel());
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}