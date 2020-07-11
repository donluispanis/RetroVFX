#include "PlasmaDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool PlasmaDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    accumulatedTime = 10.f;
    scale = 5;

    InitMath();
    InitColours();
    InitInput();

    return true;
}

void PlasmaDemo::InitMath()
{
    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
}

void PlasmaDemo::InitColours()
{
    colours.push_back(ColourStampGradients::FIRE);
    colours.push_back(ColourStampGradients::PLASMA);
    colours.push_back(ColourStampGradients::VINTAGE);

    colourMapSize = 256;
    colourMap = new Pixel[colourMapSize];
    currentColour = colours.size(); //We set current colour to the maximum so SwitchColour goes back to the first one

    SwitchColour();
}

void PlasmaDemo::InitInput()
{
    windowManager->RegisterKeyInput((int)Key::SPACE);
}

bool PlasmaDemo::Destroy()
{
    delete[] colourMap;

    Fast::DeleteMathTable(sineTable);

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
}

bool PlasmaDemo::Update(float deltaTime)
{
    UpdateInput();
    accumulatedTime += deltaTime;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float value = 0;
            int width_i = width - i;
            int height_j = height - j;

            value += sineTable[int((j * i) / (j + i + 1) * scale + accumulatedTime * 191) % mathTableSize];
            value += sineTable[int((width_i * j) / (width_i + j + 1)* scale + accumulatedTime * 157) % mathTableSize];
            value += sineTable[int((width_i * height_j) / (width_i + height_j + 1) * scale + accumulatedTime * 113) % mathTableSize];
            value += sineTable[int((i * height_j) / (i + height_j + 1) * scale + accumulatedTime * 67) % mathTableSize];
            value *= 0.25f;

            int index = Fast::Abs((int)(value * (colourMapSize - 1)));

            pixels[j * width + i] = colourMap[index];
        }
    }

    RenderText("Tap space to change colour", 5, 5, 4, Pixel(0));

    return true;
}

void PlasmaDemo::UpdateInput()
{
    bool isSpacePressed = windowManager->IsKeyPressed((int)Key::SPACE);

    if (isSpacePressed)
    {
        SwitchColour();
    }
}