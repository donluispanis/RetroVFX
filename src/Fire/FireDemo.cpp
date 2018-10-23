#include "FireDemo.h"
#include <stdlib.h>

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWidth();
    height = GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[sizeof(char)]; 

    return true;
}

bool FireDemo::Update(float fDeltaTime)
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        pixels[i].Clear();

        if (fast_rand() % 2 != 0)
            pixels[i] = Pixel(255, 0, 0);
    }

    for (int i = width * (height - 1); i >= 0; i--)
    {
        pixels[i] = Pixel(
            (pixels[i + 1 + width].R + pixels[i + width].R + pixels[i - 1 + width].R) / 3.02 + (fast_rand() % 10 == 0 ? 5 : 0),
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

unsigned long FireDemo::fast_rand() //TODO := Create my own library (?)
{
    static unsigned long x=123456789, y=362436069, z=521288629;
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