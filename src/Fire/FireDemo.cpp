#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "FireDemo.h"
#include "ColourStamp.h"

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWidth();
    height = GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[256];

    //FIRE
    interpolateColourMap({ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{255, 0, 0}}, ColourStamp{0.2f, Pixel{255, 125, 0}},
                          ColourStamp{0.4f, Pixel{255, 255, 0}}, ColourStamp{0.5f, Pixel{255, 255, 255}}, ColourStamp{1.0f, Pixel{255, 255, 255}}});

    //RETRO COOL
    //interpolateColourMap({ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{123, 245, 231}}, ColourStamp{0.2f, Pixel{0, 231, 45}},
    //                      ColourStamp{0.4f, Pixel{234, 123, 231}}, ColourStamp{0.5f, Pixel{231, 32, 126}}, ColourStamp{1.0f, Pixel{236, 231, 54}}});

    updateFireBase();

    return true;
}

void FireDemo::interpolateColourMap(std::vector<ColourStamp> colours)
{
    if (colours.size() == 0)
        ShowError("FireDemo::createColourMap => No colour map was provided");

    if (colours.size() == 1)
        for (int i = 0; i < 256; i++)
            colourMap[i] = colours[0].colour;

    if (colours.size() > 1)
    {
        unsigned char from = 0, to, way = 0;
        to = colours[1].percentage * 255;

        for (int i = 0; i < 256; i++)
        {
            if (i == to)
            {
                colours.erase(colours.begin());
                from = to;
                to = colours[1].percentage * 255;
                way = 0;
            }

            float t = (float)(to - from - way) / (to - from);
            colourMap[i] = colours[0].colour * t + colours[1].colour * (1 - t);

            way++;
        }
    }
}

void FireDemo::updateFireBase()
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        screenMapping[i] = 0;

        if (fast_rand() % 10 == 0)
            screenMapping[i] = 255;

        pixels[i] = colourMap[screenMapping[i]];
    }
}

bool FireDemo::Update(float deltaTime)
{
    updateFireInput();
    updateFireScreen();
    return true;
}

void FireDemo::updateFireInput()
{
    if (mouseKeys.leftKey.isHeld)
    {
        int x = mouseKeys.x;
        int y = mouseKeys.y;
        int sum = y * width + x;
        screenMapping[sum] = 255;
        pixels[sum] = colourMap[screenMapping[sum]];
    }
}

void FireDemo::updateFireScreen()
{
    for (int i = width * (height - 1); i >= 0; i--)
    {
        int sum = width + i;
        sum = screenMapping[i] = (screenMapping[sum + 1] + screenMapping[sum] + screenMapping[sum - 1]) / 3.02 + (fast_rand() % 4 == 0 ? 2 : 0);
        pixels[i] = colourMap[sum];
    }
}

bool FireDemo::Destroy()
{
    delete[] screenMapping;
    delete[] colourMap;

    return true;
}

unsigned long FireDemo::fast_rand() //TODO := Create my own library (?)
{
    static unsigned long x = 123456789, y = 362436069, z = 521288629;
    static unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}