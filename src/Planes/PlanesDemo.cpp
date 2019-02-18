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

    texture = new Pixel[80 * 80];
    texWidth = 80;
    texHeight = 80;
    texSize = texWidth * texHeight;

    for (int i = 0; i < texWidth; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            if (i % 20 == 0 || j % 20 == 0 || i % 20 == 1 || j % 20 == 1 || i % 20 == 2 || j % 20 == 2 || i % 20 == 3 || j % 20 == 3)
            {
                texture[j * texWidth + i] = Pixel(255);
            }
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

    int pixelScaleFactor = 4;

    int maxWidth = width / pixelScaleFactor;
    int maxHeight = height / pixelScaleFactor;
    int startingWidth = -maxWidth / 2;
    int startingHeight = maxHeight / 2;

    double _x, _y;

    //z - the incrementable variable that beggins at -300 and go to 300, because
    //the depth will be in the center of the HEIGHT
    double z = (height / 2) * -1;

    //Scales just to control de scale of the printed pixel. It is not necessary
    double scaleX = 16.0;
    double scaleY = 16.0;

    //Mode 7 - loop (Left Top to Down)
    for (int y = 0; y < height; y++)
    {

        _y = y / (z == 0 ? 1 : z); //The new _y coord generated
        if (_y < 0)
            _y *= -1;              //Control the _y because the z starting with a negative number
        _y *= scaleY;              //Increase the size using scale
        _y = fmod(_y, texHeight); //Repeat the pixel avoiding get texture out of bounds

        for (int x = 0; x < width; x++)
        {

            _x = (width / 2 - x) / (z == 0 ? 1 : z); //The new _x coord generated
            if (_x < 0)
                _x *= -1;             //Control the _x to dont be negative
            _x *= scaleX;             //Increase the size using scale
            _x = fmod(_x, texWidth); //Repeat the pixel avoiding get texture out of bounds

            //Set x,y of the view image with the _x,_y pixel in the texture
            pixels[y * width + x] = texture[Fast::Abs((int)_y * texWidth + (int)_x)];
        }

        //Increment depth
        z++;
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
        cameraPosition.X = cameraPosition.X * cosf(cameraAngle) - cameraPosition.Y * sinf(cameraAngle);
        cameraPosition.Y = cameraPosition.X * sinf(cameraAngle) + cameraPosition.Y * cosf(cameraAngle);
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