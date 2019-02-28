#include "PlasmaDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

Fast::SineTable<PlasmaDemo::tableSize> PlasmaDemo::sine = Fast::SineTable<PlasmaDemo::tableSize>();

Fast::SquareRootTable<PlasmaDemo::tableSize> PlasmaDemo::sqrt = Fast::SquareRootTable<PlasmaDemo::tableSize>();

bool PlasmaDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    accumulatedTime = 0.f;
    scale = 5;

    InitColours();
    InitInput();

    return true;
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
            
            value += sine.table[int((j * i) / (j + i + 1.f) * scale + accumulatedTime * 166) % tableSize];
            value += sine.table[int(sqrt.table[i * j] * scale + accumulatedTime * 133) % tableSize];
            value += sine.table[int(sqrt.table[(width - i) * (height - j)] * scale + accumulatedTime * 100) % tableSize];
            value += sine.table[int(sqrt.table[(i) * (height - j)] * scale + accumulatedTime * 66) % tableSize];
            value *= 0.25f;

            int index = Fast::Abs((int)(value * (colourMapSize - 1)));

            pixels[j * width + i] = colourMap[index];
        }
    }

    RenderText("Tab space to change colour", 5, 5, 4, Pixel(0));

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