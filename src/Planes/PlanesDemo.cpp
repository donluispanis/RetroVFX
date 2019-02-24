#include "PlanesDemo.h"
#include "../Utils/InputValues.h"
#include "../Utils/Pixel.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/PerlinNoise2D.h"
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

    PerlinNoise2D perlinNoise(8);
    float *noiseMap;
    int size;
    perlinNoise.Build(noiseMap, size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            pixels[j * width + i] = Pixel(255) * noiseMap[j * size + i];
        }
    }

    /*
    texWidth = 404;
    texHeight = 204;
    texSize = texWidth * texHeight;
    texture = new Pixel[texSize];

    for (int i = 0; i < texWidth; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            if (i % 20 == 0 || j % 20 == 0 || i % 20 == 1 || j % 20 == 1 || i % 20 == 2 || j % 20 == 2 || i % 20 == 3 || j % 20 == 3)
            {
                texture[j * texWidth + i] = Pixel(255);
            }
        }
    }*/

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
    float farX = 1.f, nearX = 1.f;
    float minY = 200.f, maxY = 404.f;

    UpdateInput(deltaTime);

    /*for(int i = 200; i < 604; i++)
    {
        for(int j = 200; j < 404; j++)
        {
            Point2D line1_1(farX * i, minY);
            Point2D line1_2(nearX * i, maxY);

            Point2D line2_1(i, j);
            Point2D line2_2(i + 1, j);

            Point2D intersection = CalculateIntersectionOfTwoLinesGiven4Points(line1_1, line1_2, line2_1, line2_2);

            pixels[int(intersection.Y * width + intersection.X)] = texture[(j - 200) * texWidth + int(i - 200)];
        }
    }*/

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
        //cameraAngle -= deltaTime * 0.1;
    }
    if (turnRight)
    {
        //cameraAngle += deltaTime * 0.1;
    }

    if (goForth)
    {
        //cameraPosition.X = cameraPosition.X * cosf(cameraAngle) - cameraPosition.Y * sinf(cameraAngle);
        //cameraPosition.Y = cameraPosition.X * sinf(cameraAngle) + cameraPosition.Y * cosf(cameraAngle);
    }
    if (goBack)
    {
        //cameraPosition.X += deltaTime * cosf(cameraAngle) * 20;
        //cameraPosition.Y -= deltaTime * sinf(cameraAngle) * 20;
    }

    if (goUp)
    {
        //farPlane += deltaTime * 0.1;
    }
    if (goDown)
    {
        //farPlane -= deltaTime * 0.1;
    }
}

Point2D PlanesDemo::CalculateIntersectionOfTwoLinesGiven4Points(Point2D line1_1, Point2D line1_2, Point2D line2_1, Point2D line2_2)
{
    Point2D director1 = line1_2 - line1_1;
    Point2D director2 = line2_2 - line2_1;

    float slope1 = director1.X / director1.Y;
    float slope2 = director2.X / director2.Y;

    if(director1.Y == 0.f)
    {
        slope1 = 0.f;
    }
    if(director2.Y == 0.f)
    {
        slope2 = 0.f;
    }

    float phase1 = line1_1.Y - slope1 * line1_1.X;
    float phase2 = line2_1.Y - slope2 * line2_1.X;

    Point2D intersection;

    intersection.X = (phase2 - phase1) / (slope1 - slope2);
    intersection.Y = slope1 * intersection.X + phase1;

    return intersection;
}