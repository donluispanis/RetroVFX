#include "ColourStamp.h"

FireDemo::ColourStamp::ColourStamp(float perc, Pixel col)
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

void FireDemo::ColourStamp::InterpolateColourMap(std::vector<ColourStamp> colours, Pixel *colourMap, int colourMapSize)
{
    if (colours.size() == 0)
    {
        for (int i = 0; i < colourMapSize; i++)
        {
            colourMap[i] = Pixel();
        }
    }

    if (colours.size() == 1)
    {
        for (int i = 0; i < colourMapSize; i++)
        {
            colourMap[i] = colours[0].colour;
        }
    }

    if (colours.size() > 1)
    {
        unsigned char from = 0;
        unsigned char to = colours[1].percentage * 255;
        unsigned char current = 0;

        for (int i = 0; i < colourMapSize; i++)
        {
            if (i == to)
            {
                colours.erase(colours.begin());
                from = to;
                to = colours[1].percentage * 255;
                current = 0;
            }

            float t = (float)(to - from - current) / (to - from);
            colourMap[i] = colours[0].colour * t + colours[1].colour * (1 - t);

            current++;
        }
    }
}