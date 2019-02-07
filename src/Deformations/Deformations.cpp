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
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            DrawPixel(i, j, deltaTime, DefaultXModifier, DefaultYModifier);
        }
    }

    return true;
}

void Deformations::DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier)
{
    int scaledX = x * texWidth / (float)width;
    int scaledY = y * texHeight / (float)height;

    int texX = (this->*xModifier)(scaledX, deltaTime) % texWidth;
    int texY = (this->*yModifier)(scaledY, deltaTime) % texHeight;

    pixels[y * width + x] = texture[texY * texWidth + texX];
}

int Deformations::DefaultXModifier(int x, float deltaTime)
{
    int xCenter = width * texWidth / (float)width / 2;
    float scale = Fast::Abs(xCenter - x) / (float)(xCenter) + 1;

    //std::cout << xCenter << " " << x << " " << xCenter - x << std::endl;
    return x * scale;
}

int Deformations::DefaultYModifier(int y, float deltaTime)
{
    return y;
}