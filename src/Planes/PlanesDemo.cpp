#include "PlanesDemo.h"
#include "../Utils/InputValues.h"
#include "../Utils/Pixel.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>
#include <cmath>
bool PlanesDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    texture = nullptr;

    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);

    cameraPosition.X = 500.f;
    cameraPosition.Y = 500.f;
    cameraAngle = 0.f;

    nearPlane = 0.01f;
    farPlane = 0.5f;

    texture = new Pixel[256 * 256];
    texWidth = 256;
    texHeight = 256;
    texSize = texWidth * texHeight;

    for (int i = 0; i < texWidth; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            float intensity = char(i ^ j) / float(256);
            texture[j * texWidth + i] = Pixel(char(255 * 255 * intensity), 125, 255 * (1 - intensity));
        }
    }

    RegisterInput();

    return true;
}

void PlanesDemo::RegisterInput()
{
    windowManager->RegisterKeyInput((int)Key::Q);
    windowManager->RegisterKeyInput((int)Key::W);
    windowManager->RegisterKeyInput((int)Key::E);
    windowManager->RegisterKeyInput((int)Key::A);
    windowManager->RegisterKeyInput((int)Key::S);
    windowManager->RegisterKeyInput((int)Key::D);
}

bool PlanesDemo::Destroy()
{
    return true;
}

bool PlanesDemo::Update(float deltaTime)
{
    UpdateInput(deltaTime);

    float px, py;
    int count = 0;

    int startingHeight = height *0.33;

    for (int j = startingHeight; j < height; j++)
    {
        count++;
        py = (height - j) * (1 - j / float(height));
        for (int i = 0; i < width; i++)
        {
            px = i;

            pixels[j * width + i] = texture[int((int(py) % texHeight) * texWidth + int(px) % texWidth) % texSize];
        }
    }

    RenderText("dfsgdftgh", 5, 5, 2, Pixel(255));
    return true;
}

void PlanesDemo::UpdateInput(float deltaTime)
{
    bool turnLeft = windowManager->IsKeyHeld((int)Key::A);
    bool turnRight = windowManager->IsKeyHeld((int)Key::D);
    bool goForth = windowManager->IsKeyHeld((int)Key::W);
    bool goBack = windowManager->IsKeyHeld((int)Key::S);
    bool goUp = windowManager->IsKeyHeld((int)Key::Q);
    bool goDown = windowManager->IsKeyHeld((int)Key::E);

    if (turnLeft)
    {
        cameraAngle -= deltaTime * 0.1;
    }
    if (turnRight)
    {
        cameraAngle += deltaTime * 0.1;
    }

    if (goForth)
    {
        cameraPosition.Y += deltaTime * 200;
    }
    if (goBack)
    {
        cameraPosition.X += deltaTime * cosf(cameraAngle) * 20;
        cameraPosition.Y -= deltaTime * sinf(cameraAngle) * 20;
    }

    if (goUp)
    {
        farPlane += deltaTime * 0.1;
    }
    if (goDown)
    {
        farPlane -= deltaTime * 0.1;
    }
}