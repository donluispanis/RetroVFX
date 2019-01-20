#pragma once

#include <vector>

#include "../Utils/Pixel.h"

struct ColourStamp
{
    float percentage;
    Pixel colour;

    ColourStamp(float perc, Pixel col);
    static void GenerateGradient(std::vector<ColourStamp> colours, Pixel* colourMap, int colourMapSize);
};