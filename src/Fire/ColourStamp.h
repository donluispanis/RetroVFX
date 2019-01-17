#pragma once

#include <vector>

#include "FireDemo.h"
#include "../ClassicDemoTemplate/Pixel.h"

struct FireDemo::ColourStamp
{
    float percentage;
    Pixel colour;

    ColourStamp(float perc, Pixel col);
    static void InterpolateColourMap(std::vector<ColourStamp> colours, Pixel* colourMap, int colourMapSize);
};