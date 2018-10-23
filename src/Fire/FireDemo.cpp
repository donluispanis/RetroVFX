#include "FireDemo.h"
#include <stdlib.h>

bool FireDemo::Init()
{
    pixels = GetScreenPixels();
    width = GetWidth();
    height = GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[256]; 

    for(int i = 0; i < 256; i++)
        colourMap[i].R = (unsigned char)i;

    return true;
}

bool FireDemo::Update(float fDeltaTime)
{
    for (int i = width * (height - 1); i < width * height; i++)
    {
        screenMapping[i] = 0;

        if (fast_rand() % 2 != 0)
            screenMapping[i] = 255;
        
        pixels[i] = Pixel(255,0,0); //fast equivalent to -> pixels[i] = colourMap[screenMapping[i]];
        
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