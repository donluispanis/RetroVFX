#include "ColourStamp.h"

FireDemo::ColourStamp::ColourStamp(float perc, ClassicDemoTemplate::Pixel col)
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