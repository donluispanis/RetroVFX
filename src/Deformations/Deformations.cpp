#include "Deformations.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
#include "../Utils/InputValues.h"
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
    RegisterModifiers();
    RegisterInput();

    BMP::OpenRGBImage("assets/img/tiger.bmp", texture, texWidth, texHeight);

    return true;
}

void Deformations::InitMath()
{
    mathTableSize = 2048;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);
}

void Deformations::RegisterModifiers()
{
    modifiers.push_back(std::pair<delegate, delegate>(DefaultXModifier, DefaultYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(DefaultXModifier, WaveYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(WaveXModifier, DefaultYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(WaveXModifier, WaveYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(MosaicXModifier, MosaicYModifier));

    texts.push_back("1. Raw image");
    texts.push_back("2. Horizontal wave");
    texts.push_back("3. Vertical wave");
    texts.push_back("4. Diamond");
    texts.push_back("5. Mosaic");
    
    currentModifierIndex = 0;
    currentModifier = modifiers[currentModifierIndex];
}

void Deformations::RegisterInput()
{
    windowManager->RegisterKeyInput((int)Key::SPACE);
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
    UpdateInput();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            DrawPixel(i, j, deltaTime, currentModifier.first, currentModifier.second);
        }
    }

    accumulatedTime += deltaTime;
    RenderText("Tap space to change modifier", 5, 5, 2, Pixel(255));
    RenderText(texts[currentModifierIndex], 5, 25, 4, Pixel(255, 255, 150));

    return true;
}

void Deformations::UpdateInput()
{
    bool changeCurrentModifier = windowManager->IsKeyPressed((int)Key::SPACE);
    if(changeCurrentModifier)
    {
        UpdateCurrentModifier();
    }
}

void Deformations::UpdateCurrentModifier()
{
    currentModifierIndex++;

    if(currentModifierIndex == modifiers.size())
    {
        currentModifierIndex = 0;
    }

    currentModifier = modifiers[currentModifierIndex];
}

void Deformations::DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier)
{
    int scaledX = int(x * texWidth / (float)width) % texWidth;
    int scaledY = int(y * texHeight / (float)height) % texHeight;

    int newX = (this->*xModifier)(x, y);
    int newY = (this->*yModifier)(x, y);

    if (IsPixelOutOfBounds(newX, newY))
    {
        return;
    }

    pixels[newY * width + newX] = texture[scaledY * texWidth + scaledX];
}

int Deformations::DefaultXModifier(int x, int y)
{
    return x;
}

int Deformations::DefaultYModifier(int x, int y)
{
    return y;
}

int Deformations::MosaicXModifier(int x, int y)
{
    return x + sineTable[(x * 20 + int(500 * accumulatedTime)) % mathTableSize ] * 20;
}

int Deformations::MosaicYModifier(int x, int y)
{
    return y + sineTable[(y * 20 + int(500 * accumulatedTime)) % mathTableSize ] * 20;
}

int Deformations::WaveXModifier(int x, int y)
{
    return x + sineTable[(y * 20 + int(accumulatedTime * 400)) % mathTableSize] * 20;
}

int Deformations::WaveYModifier(int x, int y)
{
    return y + sineTable[(x * 20 + int(accumulatedTime * 400)) % mathTableSize] * 20;
}