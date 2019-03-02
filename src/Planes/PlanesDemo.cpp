#include "PlanesDemo.h"
#include "../Utils/NoiseGenerator.h"
#include "../Utils/InputValues.h"
#include "../Utils/Point3D.h"
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

    texWidth = 512;
    texHeight = 512;
    texSize = texHeight * texWidth;
    texture = new Pixel[texSize];

    NoiseGenerator noiseGenerator = NoiseGenerator(512, 512, 4);
    float *noiseMap = noiseGenerator.Generate2DNoise();

    for (int i = 0; i < texWidth; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            texture[j * texWidth + i] = Pixel(255) * noiseMap[j * texHeight + i];
        }
    }

    for (int i = 0; i < 512; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            if (i % 64 == 0 || i % 64 == 1 || i % 64 == 2 || i % 64 == 3 || j % 64 == 0 || j % 64 == 1 || j % 64 == 2 || j % 64 == 3)
            {
                pixels[j * width + i] = Pixel(0);
            }
        }
    }

    cameraAngle = 0.f;

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
    delete[] texture;
    return true;
}

bool PlanesDemo::Update(float deltaTime)
{
    float farX = 1.f, nearX = 1.f;
    float minY = 200.f, maxY = 404.f;

    UpdateInput(deltaTime);

    const int depth = 500;

            ClearScreen(Pixel(0));
    for (int i = -width / 2, nw = width / 2; i < nw; i++)
    {
        for (int j = 0, nh = height *2 / 3; j < nh; j++)
        {
            const int horizon = 0;
            const int fieldOfView = 200;
            const float scale = 100.f;

            Point3D p(i, fieldOfView, j + horizon);
            Point2D s(p.X / p.Z, p.Y / p.Z);

            s *= scale;

            float coss = cosf(cameraAngle);
            float sinn = sinf(cameraAngle);

            Point2D r(s.X * coss - s.Y * sinn,
                        s.X * sinn + s.Y * coss);

            Pixel pix = texture[Fast::Abs((int(r.Y + cameraPosition.Y * scale) % texHeight) * texWidth + 
                                                            int(r.X + cameraPosition.X * scale) % texWidth)];

            float sc = pix.R / 500.f;
            int a = (depth * 2 * sc) * (p.Z / float(height / 2));

            pixels[(j - a + nh) * width + (i + nw)] = pix;
        }
    }

    //RenderText("dfsgdftgh", 5, 5, 2, Pixel(255));
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
        cameraAngle += deltaTime;
    }
    if (turnRight)
    {
        cameraAngle -= deltaTime;
    }

    if (goForth)
    {
        cameraPosition.X -= deltaTime * sinf(cameraAngle);
        cameraPosition.Y += deltaTime * cosf(cameraAngle);
    }
    if (goBack)
    {
        cameraPosition.X += deltaTime * sinf(cameraAngle);
        cameraPosition.Y -= deltaTime * cosf(cameraAngle);
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

    if (director1.Y == 0.f)
    {
        slope1 = 0.f;
    }
    if (director2.Y == 0.f)
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