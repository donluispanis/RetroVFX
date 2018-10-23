#include "FireDemo.h"
#include <stdlib.h>

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWidth();
    height = GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new unsigned char[sizeof(char)];

    return true;
}

bool FireDemo::Update(float fDeltaTime)
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        pixels[i].Clear();
        
        if (rand() % 2 != 0)
            pixels[i] = Pixel(255, 0, 0);
    }

    for (int i = GetWidth() * (GetHeight() - 1); i >= 0; i--)
    {
        pixels[i] = Pixel(
            (pixels[i + 1 + width].R + pixels[i + width].R + pixels[i - 1 + width].R) / 3.02 + (rand() % 10 == 0 ? 5 : 0),
            0,
            0);
    }
    return true;
}

bool FireDemo::Destroy()
{
    delete[] screenMapping;
    delete[] colourMap;

    return true;
}