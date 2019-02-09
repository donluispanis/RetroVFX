#include "Deformations.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>

bool Deformations::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    accumulatedTime = 0.f;

    InitMath();

    BMP::OpenRGBImage("assets/img/tiger.bmp", texture, texWidth, texHeight);

    return true;
}

void Deformations::InitMath()
{
    mathTableSize = 2048;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);
}

bool Deformations::Destroy()
{
    BMP::CloseRGBImage(texture);
    Fast::DeleteMathTable(sineTable);
    Fast::DeleteMathTable(cosineTable);

    return true;
}

bool Deformations::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            DrawPixel(i, j, deltaTime, WaveXModifier, WaveYModifier);
        }
    }

    return true;
}

void Deformations::DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier)
{
    int scaledX = int(x * texWidth / (float)width) % texWidth;
    int scaledY = int(y * texHeight / (float)height) % texHeight;

    int newX = (this->*xModifier)(x);
    int newY = (this->*yModifier)(y);

    if (IsPixelOutOfBounds(newX, newY))
    {
        return;
    }

    pixels[newY * width + newX] = texture[scaledY * texWidth + scaledX];
}

int Deformations::DefaultXModifier(int x)
{
    int xCenter = width * texWidth / (float)width / 2;
    float scale = Fast::Abs(xCenter - x) / (float)(xCenter) + 1;

    //std::cout << xCenter << " " << x << " " << xCenter - x << std::endl;
    return x * scale;
}

int Deformations::DefaultYModifier(int y)
{
    return y;
}

int Deformations::WaveXModifier(int x)
{
    return x + sineTable[(x * 20 + int(500 * accumulatedTime)) % mathTableSize ] * 20;
}

int Deformations::WaveYModifier(int y)
{
    return y + sineTable[(y * 20 + int(500 * accumulatedTime)) % mathTableSize ] * 20;
}