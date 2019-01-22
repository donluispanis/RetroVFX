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

    return true;
}

bool DotTunnelDemo::Update(float deltaTime)
{
    int px = width/2, py = height/2, radius = 200;
    float increment = 1 / (float)radius;    //For a correct circle to be drawn, we need to know how fast we increment
    int x, y;
    float fx, fy;

    for (float i = 0; i < Fast::PI / 4; i += increment)
    {
        fx = sineTable[int(i * mathTableSize)] * radius;   //Calculate x deviation value
        fy = cosineTable[int(i * mathTableSize)] * radius;   //Calculate y deviation value
        x = fx; //Clamp to an integer value
        y = fy; //Clamp to an integer value
        fx -= x;    //Obtain a value between 0 and 1 to be used in alpha antialiasing calculation

        //Draw each one of the 8 semiquadrants of the circle
        pixels[(py + y) * width + (px + x)] = Pixel{255,255,255};
        pixels[(py + x) * width + (px + y)] = Pixel{255,255,255};
        pixels[(py + x) * width + (px - y)] = Pixel{255,255,255};
        pixels[(py + y) * width + (px - x)] = Pixel{255,255,255};
        pixels[(py - y) * width + (px - x)] = Pixel{255,255,255};
        pixels[(py - x) * width + (px - y)] = Pixel{255,255,255};
        pixels[(py - x) * width + (px + y)] = Pixel{255,255,255};
        pixels[(py - y) * width + (px + x)] = Pixel{255,255,255};
    }

    RenderText("DotTunnel effect.", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}