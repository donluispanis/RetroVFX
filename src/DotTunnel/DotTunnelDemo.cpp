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
    defaultCircle.radius = 20;
    defaultCircle.rotation = 0;
    defaultCircle.density = 0.05;
    defaultCircle.colour = Pixel(0, 0, 0);

    signX = 1;
    signY = 1;

    InitCircleQueue();

    return true;
}

void DotTunnelDemo::InitCircleQueue()
{
    for (int i = 0; i < circleCount; i++)
    {
        circles.push_back(Circle{defaultCircle.x, defaultCircle.y, (defaultCircle.radius * circleCount) / (circleCount - i + 1),
                                 defaultCircle.rotation, defaultCircle.density, Pixel(255, 255, 255)});
    }
}

bool DotTunnelDemo::Update(float deltaTime)
{
    UpdateCircleQueue();
    UpdateSign(deltaTime);

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

    for (auto &c : circles)
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

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {
        x = sineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.x;
        y = cosineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.y;

        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
        {
            continue;
        }

        pixels[y * width + x] = c.colour;
    }
}

void DotTunnelDemo::UpdateCircle(Circle &c)
{
    float dt = windowManager->GetDeltaTime();

    c.radius += c.radius * dt * 0.3;
    c.y += dt * 20 * signY;
    c.x += dt * 20 * signX;
    c.colour = c.colour + Pixel(1, 1, 1);

    c.colour.B = 255 / c.radius;
    c.colour.G = int(255 * c.radius) % 255;
}

void DotTunnelDemo::UpdateSign(float deltaTime)
{
    int modulus = 1 / (deltaTime / 5) + 1;

    if (Fast::Rand() % modulus == 0)
    {
        signX = -signX;
    }
    if (Fast::Rand() % modulus == 0)
    {
        signY = -signY;
    }
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