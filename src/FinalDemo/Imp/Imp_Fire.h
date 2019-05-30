#pragma once

#include "../../Utils/Pixel.h"

class Imp_Fire
{
public:
    void InitFire(int width, int height, Pixel* pixels);
    void UpdateFire(float deltaTime, float accumulatedTime, float startTime);
    void CloseFire();

private:
    void InitBigFireText(int size, int value);
    void InitSmallFireText(int size, int value);
    void DrawBigFireText();
    void DrawSmallFireText();
    void DrawCharacterOnFireMap(unsigned char *map, int width, unsigned char value, int x, int y, char character, int scale);

    unsigned char *screenMapping;
    unsigned char *fireMapping;
    Pixel *colourMap;
    int colourMapSize = 256;

    int bigFireScale;
    int bigFireHeight;
    int bigFireCharCount;
    int bigFireCharSize;
    int bigFireTextStart;

    int smallFireScale;
    int smallFireHeight;
    int smallFireCharCount;
    int smallFireCharSize;
    int smallFireTextStart;

    int width, height;
    Pixel* pixels;
};