#include "PlanesDemo.h"
#include "../Utils/BMP.h"
#include "../Utils/InputValues.h"
#include "../Utils/Pixel.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <cmath>
#include <string>

bool PlanesDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    texture = nullptr;

    if(!BMP::TryOpenImageInDifferentLocations("assets/img/groundsoil.bmp", texture, texWidth, texHeight))
    {
        return false;
    }

    texSize = texHeight * texWidth;

    cameraAngle = 0.f;

    RegisterInput();

    RenderText("Use W, A, S, D to move around", 5, 5, 2, Pixel(255));
    RenderText("Use Q / E to go up / down", 5, 20, 2, Pixel(255));
    RenderText("Use Z / X to create relief on the terrain", 5, 35, 2, Pixel(255));

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
    windowManager->RegisterKeyInput((int)Key::Z);
    windowManager->RegisterKeyInput((int)Key::X);
}

bool PlanesDemo::Destroy()
{
    BMP::CloseRGBImage(texture);
    return true;
}

bool PlanesDemo::Update(float deltaTime)
{
    ClearScreen(0, height / 2, width, height, Pixel(0));
    UpdateInput(deltaTime);

    float cosine = cosf(cameraAngle);
    float sine = sinf(cameraAngle);

    for (int j = 0, nh = height / 2; j < nh; j++)
    {
        float distanceFactor = (j / float(height / 2));

        for (int i = -width / 2, nw = width / 2; i < nw; i++)
        {
            Point2D projectedPoint(i / (float)j, fieldOfView / (float)j);
            projectedPoint *= textureScale;

            Point2D rotatedPoint(projectedPoint.X * cosine - projectedPoint.Y * sine,
                                 projectedPoint.X * sine + projectedPoint.Y * cosine);

            Pixel colour = texture[Fast::Abs((int(rotatedPoint.Y + cameraPosition.Y) % texHeight) * texWidth +
                                             int(rotatedPoint.X + cameraPosition.X) % texWidth)] *
                           distanceFactor;

            float colourBrightness = ((colour.R * 0.3) + (colour.G * 0.59) + (colour.B * 0.11)) * 0.004f; // * 1 / 256
            int textureDesplacement = (bumpLevel * colourBrightness) * distanceFactor;

            pixels[(j - textureDesplacement + nh) * width + (i + nw)] = colour;
        }
    }

    return true;
}

void PlanesDemo::UpdateInput(float deltaTime)
{
    bool turnLeft = windowManager->IsKeyHeld((int)Key::A);
    bool turnRight = windowManager->IsKeyHeld((int)Key::D);
    bool goForth = windowManager->IsKeyHeld((int)Key::W);
    bool goBack = windowManager->IsKeyHeld((int)Key::S);
    bool bumpUp = windowManager->IsKeyHeld((int)Key::Z);
    bool bumpDown = windowManager->IsKeyHeld((int)Key::X);
    bool increaseTextureSize = windowManager->IsKeyHeld((int)Key::Q);
    bool decreaseTextureSize = windowManager->IsKeyHeld((int)Key::E);

    if (turnLeft)
    {
        cameraAngle += deltaTime;
    }
    if (turnRight)
    {
        cameraAngle -= deltaTime;
    }

    if (goForth)
    {
        cameraPosition.X -= deltaTime * sinf(cameraAngle) * 40;
        cameraPosition.Y += deltaTime * cosf(cameraAngle) * 40;
    }
    if (goBack)
    {
        cameraPosition.X += deltaTime * sinf(cameraAngle) * 40;
        cameraPosition.Y -= deltaTime * cosf(cameraAngle) * 40;
    }

    if (bumpUp)
    {
        bumpLevel += deltaTime * 20;
    }
    if (bumpDown)
    {
        bumpLevel -= deltaTime * 20;
        if (bumpLevel < 0.f)
        {
            bumpLevel = 0.f;
        }
    }

    if (increaseTextureSize)
    {
        textureScale += deltaTime * 20;
    }
    if (decreaseTextureSize)
    {
        textureScale -= deltaTime * 20;
        if (textureScale < 0.f)
        {
            textureScale = 0.f;
        }
    }
}