#include "PlasmaDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

#include <cmath>

bool PlasmaDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    accumulatedTime = 0.f;

    InitMath();
    InitColours();

    return true;
}

void PlasmaDemo::InitMath()
{
    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);
    sqrtTable = Fast::GenerateSqrtTable(width * height);
}

void PlasmaDemo::InitColours()
{
    colours.push_back(ColourStampGradients::VINTAGE);
    colours.push_back(ColourStampGradients::RAINBOW);
    colours.push_back(ColourStampGradients::FIRE);
    colours.push_back(ColourStampGradients::COOL);

    colourMapSize = 256;
    colourMap = new Pixel[colourMapSize];
    currentColour = colours.size(); //We set cuurent colour to the maximum so SwitchColour goes back to the first one

    SwitchColour();
}

bool PlasmaDemo::Destroy()
{
    delete[] colourMap;

    Fast::DeleteMathTable(sineTable);
    Fast::DeleteMathTable(cosineTable);
    Fast::DeleteMathTable(sqrtTable);

    return true;
}

void PlasmaDemo::SwitchColour()
{
    currentColour++;

    if (currentColour >= colours.size())
    {
        currentColour = 0;
    }

    ColourStamp::GenerateGradient(colours[currentColour], colourMap, colourMapSize);

    for (int i = 0; i < colourMapSize; i++)
    {
    }
}

bool PlasmaDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;
    int scale = 5;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float value = 0;
            value += sineTable[int((j * i) / (j + i + 1.f) * scale + accumulatedTime * 166) % mathTableSize];
            value += sineTable[int(sqrtTable[i * j] * scale + accumulatedTime * 133) % mathTableSize];
            value += sineTable[int(sqrtTable[(width - i) * (height - j)] * scale + accumulatedTime * 100) % mathTableSize];
            value += sineTable[int(sqrtTable[(i) * (height - j)] * scale + accumulatedTime * 66) % mathTableSize];
            value *= 0.25f;

            //value = Fast::Abs(value * (colourMapSize - 1));
            int x = Fast::Abs((int)(value * (colourMapSize - 1))) % colourMapSize;

            pixels[j * width + i] = colourMap[x];
        }
    }

    RenderText("Plasma", 5, 5, 2, Pixel(255));

    return true;
}
