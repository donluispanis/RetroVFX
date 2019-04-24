#include "FireDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool FireDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    screenMapping = new unsigned char[width * height];
    colourMap = new Pixel[colourMapSize];
    currentColour = 0;
    fireIntensity = 0.0;

    InitInput();
    InitialiseFireColours();
    UpdateFireBase();

    return true;
}

void FireDemo::InitInput()
{
    windowManager->RegisterKeyInput((int)Key::UP);
    windowManager->RegisterKeyInput((int)Key::DOWN);
    windowManager->RegisterKeyInput((int)Key::SPACE);
}

void FireDemo::InitialiseFireColours()
{
    colours.push_back(ColourStampGradients::FIRE);
    colours.push_back(ColourStampGradients::COOL);
    colours.push_back(ColourStampGradients::VINTAGE);
}

void FireDemo::UpdateFireBase()
{
    ColourStamp::GenerateGradient(colours[currentColour], colourMap, colourMapSize);

    for (int i = width * (height - 1), n = width * height; i < n; i++)
    {
        screenMapping[i] = 0;

        if (Fast::Rand() % 10 == 0)
        {
            screenMapping[i] = 255;
        }

        pixels[i] = colourMap[screenMapping[i]];
    }
}

bool FireDemo::Update(float deltaTime)
{
    UpdateFireScreen();
    RenderText("Press space to change the colour of the fire.", 5, 5, 2, Pixel{255, 255, 255});
    RenderText("Press up/down to change the intensity of the fire.", 5, 20, 2, Pixel{255, 255, 255});
    return true;
}

void FireDemo::UpdateFireScreen()
{
    UpdateInput();

    for (int i = width * (height - 1); i >= 0; i--)
    {
        int sum = width + i;
        sum = screenMapping[i] = (screenMapping[sum + 1] + screenMapping[sum] + screenMapping[sum - 1]) / (3.03 + fireIntensity) + (Fast::Rand() % 4 == 0 ? 2 : 0);
        pixels[i] = colourMap[sum];
    }
}

void FireDemo::UpdateInput()
{
    bool isSpacePressed = windowManager->IsKeyPressed((int)Key::SPACE);
    bool isIntensityIncreasing = windowManager->IsKeyHeld((int)Key::UP);
    bool isIntensityDecreasing = windowManager->IsKeyHeld((int)Key::DOWN);

    if (isSpacePressed)
    {
        SwitchColour();
    }
    if (isIntensityDecreasing)
    {
        fireIntensity += windowManager->GetDeltaTime() * 0.02;
    }
    if (isIntensityIncreasing && fireIntensity > -0.029)
    {
        fireIntensity -= windowManager->GetDeltaTime() * 0.02;
    }
}

void FireDemo::SwitchColour()
{
    currentColour++;

    if (currentColour >= colours.size())
    {
        currentColour = 0;
    }

    ColourStamp::GenerateGradient(colours[currentColour], colourMap, colourMapSize);
}

bool FireDemo::Destroy()
{
    delete[] screenMapping;
    delete[] colourMap;

    return true;
}