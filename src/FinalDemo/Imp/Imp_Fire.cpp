#include "../../Utils/ColourStampGradients.h"
#include "Imp_Includes.h"

void FinalDemo::InitFire()
{
    screenMapping = new unsigned char[width / 2 * height / 2];
    fireMapping = new unsigned char[width / 2 * height / 2];
    colourMap = new Pixel[colourMapSize];

    for (int i = 0, n = width / 2 * height / 2; i < n; i++)
    {
        fireMapping[i] = 0;
    }
    for (int i = 0, nw = width / 2; i < nw; i++)
    {
        fireMapping[(int)(400 + 25 * sin(i * 0.1f)) * nw + i] = 1;
    }

    ColourStamp::GenerateGradient(ColourStampGradients::FIRE, colourMap, colourMapSize);
}

void FinalDemo::CloseFire()
{
    delete screenMapping;
    delete fireMapping;
    delete colourMap;
}