#pragma once

#include "../ClassicDemoTemplate.h"
#include "FireDemo.h"

struct FireDemo::ColourStamp
{
    float percentage;
    ClassicDemoTemplate::Pixel colour;

    ColourStamp(float perc, Pixel col)
    {
        if (perc > 1.0f)
        {
            percentage = 1.0f;
        }
        else if (perc < 0.0f)
        {
            percentage = 0.0f;
        }
        else
        {
            percentage = perc;
        }

        colour = col;
    }
};