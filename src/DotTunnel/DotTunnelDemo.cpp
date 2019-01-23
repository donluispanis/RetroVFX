#include "DotTunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/Fast.h"
#include "Circle.h"
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

    return true;
}

bool DotTunnelDemo::Update(float deltaTime)
{

    int px = width / 2, py = height / 2, radius = 320;
    static Circle c{px, py, radius, 0.0, 0.05};
    ClearCircle(c);
    static float acc = 0;
    acc += windowManager->GetDeltaTime();
    if (acc > 0.1)
    {
        c.rotation += 1;
        acc = 0;
    }
    DrawCircle(c, Pixel(255, 255, 255));

    RenderText("DotTunnel effect.", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void DotTunnelDemo::DrawCircle(const Circle &c, const Pixel &colour)
{
    float increment = 1 / (float)(c.radius * c.density);
    int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {

        x = sineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius;
        y = cosineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius;

        if(x < 0){
            int das = x;
        }
        //Draw each one of the 8 semiquadrants of the circle
        pixels[(c.y + y) * width + (c.x + x)] = colour;
    }
}

void DotTunnelDemo::ClearCircle(const Circle &circle)
{
    DrawCircle(circle, Pixel());
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}