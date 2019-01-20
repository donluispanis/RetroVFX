#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "FireDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
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

    InitialiseFireColours();
    UpdateFireBase();

    return true;
}

void FireDemo::InitialiseFireColours()
{
    std::vector<ColourStamp> fireColour = {ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{255, 0, 0}},
                                           ColourStamp{0.2f, Pixel{255, 125, 0}}, ColourStamp{0.4f, Pixel{255, 255, 0}}, ColourStamp{0.5f, Pixel{255, 255, 255}},
                                           ColourStamp{1.0f, Pixel{255, 255, 255}}};

    std::vector<ColourStamp> coolColour = {ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{123, 245, 231}},
                                           ColourStamp{0.2f, Pixel{0, 231, 45}}, ColourStamp{0.4f, Pixel{234, 123, 231}}, ColourStamp{0.5f, Pixel{231, 32, 126}},
                                           ColourStamp{1.0f, Pixel{236, 231, 54}}};

    std::vector<ColourStamp> vintageColour = {ColourStamp{0.0f, Pixel{0, 0, 0}}, ColourStamp{0.02f, Pixel{0, 0, 0}}, ColourStamp{0.1f, Pixel{123, 123, 123}},
                                              ColourStamp{0.2f, Pixel{255, 255, 255}}, ColourStamp{1.0f, Pixel{255, 255, 255}}};

    colours.push_back(fireColour);
    colours.push_back(coolColour);
    colours.push_back(vintageColour);
}

void FireDemo::UpdateFireBase()
{
    ColourStamp::GenerateGradient(colours[currentColour], colourMap, colourMapSize);

    for (int i = width * (height - 1); i < width * height; i++)
    {
        screenMapping[i] = 0;

        if (Fast::Rand() % 10 == 0)
            screenMapping[i] = 255;

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
    bool isSpacePressed = windowManager->IsKeyDown((int)Key::SPACE);

    if (isSpacePressed && !isSpaceHeld)
    {
        SwitchColour();
        isSpaceHeld = true;
    }
    else if (!isSpacePressed)
    {
        isSpaceHeld = false;
    }

    if (windowManager->IsKeyDown((int)Key::DOWN))
    {
        fireIntensity += windowManager->GetDeltaTime() * 0.02;
    }
    if (windowManager->IsKeyDown((int)Key::UP) && fireIntensity > -0.029)
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