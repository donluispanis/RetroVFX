#include "FireDemo.h"
#include <stdlib.h>

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWidth();
    height = GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[256];

    createColourMap({ColourStamp{0, Pixel{0,0,0}}, ColourStamp{0, Pixel{255,255,255}}});

    return true;
}

bool FireDemo::Update(float fDeltaTime)
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        screenMapping[i] = 0;

        if (fast_rand() % 2 != 0)
            screenMapping[i] = 255;

        pixels[i] = Pixel(255, 0, 0); //fast equivalent to -> pixels[i] = colourMap[screenMapping[i]];
    }

    for (int i = width * (height - 1); i >= 0; i--)
    {
        int sum = width + i;
        sum = screenMapping[i] = (screenMapping[sum + 1] + screenMapping[sum] + screenMapping[sum - 1]) / 3.02 + (fast_rand() % 10 == 0 ? 5 : 0);
        pixels[i] = colourMap[sum];
    }
    return true;
}

bool FireDemo::Destroy()
{
    delete[] screenMapping;
    delete[] colourMap;

    return true;
}

void FireDemo::createColourMap(std::vector<ColourStamp> colours)
{
    if (colours.size() == 0)
        ShowError("FireDemo::createColourMap => No colour map was provided");

    if (colours.size() == 1)
        for (int i = 0; i < 256; i++)
            colourMap[i] = colours[0].colour;

    if (colours.size() > 1)
    {
        char from, to, counter;
        from = 0;
        counter = 1;
        to = colours[1].percentage * 255;

        float t = 1.f, tprima = 0.f;

        for (int i = 0; i < 256; i++)
        {
            

            t = (float)(255 - i) / 255;
            tprima = 1 - t;
            colourMap[i].R = colours[0].colour.R * t + colours[1].colour.R * tprima;
            colourMap[i].G = colours[0].colour.G * t + colours[1].colour.G * tprima;
            colourMap[i].B = colours[0].colour.B * t + colours[1].colour.B * tprima;
        }
    }
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