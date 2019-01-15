#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "FireDemo.h"
#include "ColourStamp.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/Pixel.h"
#include "../ClassicDemoTemplate/IWindowManager.h"

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWindowManager()->GetWidth();
    height = GetWindowManager()->GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[colourMapSize];

    //FIRE
    ColourStamp::InterpolateColourMap(
        {ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{255, 0, 0}}, ColourStamp{0.2f, Pixel{255, 125, 0}}, 
        ColourStamp{0.4f, Pixel{255, 255, 0}}, ColourStamp{0.5f, Pixel{255, 255, 255}}, ColourStamp{1.0f, Pixel{255, 255, 255}}}, 
        colourMap, colourMapSize);

    //RETRO COOL
    //interpolateColourMap({ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{123, 245, 231}}, ColourStamp{0.2f, Pixel{0, 231, 45}},
    //                      ColourStamp{0.4f, Pixel{234, 123, 231}}, ColourStamp{0.5f, Pixel{231, 32, 126}}, ColourStamp{1.0f, Pixel{236, 231, 54}}});

    UpdateFireBase();

    return true;
}

void FireDemo::UpdateFireBase()
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        screenMapping[i] = 0;

        if (Fast::Rand() % 10 == 0)
            screenMapping[i] = 255;

        pixels[i] = colourMap[screenMapping[i]];
    }
}

bool FireDemo::Update(float deltaTime)
{
    UpdateFireScreen();
    return true;
}

void FireDemo::UpdateFireScreen()
{
    for (int i = width * (height - 1); i >= 0; i--)
    {
        int sum = width + i;
        sum = screenMapping[i] = (screenMapping[sum + 1] + screenMapping[sum] + screenMapping[sum - 1]) / 3.02 + (Fast::Rand() % 4 == 0 ? 2 : 0);
        pixels[i] = colourMap[sum];
    }
}

bool FireDemo::Destroy()
{
    delete[] screenMapping;
    delete[] colourMap;

    return true;
}