#pragma once

#include "FireDemo.h"
#include "../ClassicDemoTemplate/Pixel.h"

struct FireDemo::ColourStamp
{
    float percentage;
    ClassicDemoTemplate::Pixel colour;

    ColourStamp(float perc, Pixel col);
};