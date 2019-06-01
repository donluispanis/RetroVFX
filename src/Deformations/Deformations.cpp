#include "Deformations.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
#include "../Utils/InputValues.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

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

    if(!BMP::TryOpenImageInDifferentLocations("assets/img/lena.bmp", texture, texWidth, texHeight))
    {
        return false;
    }

    offsetX = texWidth;
    offsetY = texHeight;

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
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::DefaultXModifier, &Deformations::DefaultYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::DefaultXModifier, &Deformations::TransversalWaveYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::LongitudinalWaveXModifier, &Deformations::DefaultYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::TransversalWaveXModifier, &Deformations::TransversalWaveYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::LongitudinalWaveXModifier, &Deformations::LongitudinalWaveYModifier));
    modifiers.push_back(std::pair<delegate, delegate>(&Deformations::FlagXModifier, &Deformations::FlagYModifier));

    texts.push_back("1. Raw image");
    texts.push_back("2. Transversal wave");
    texts.push_back("3. Longitudinal wave");
    texts.push_back("4. Diamond");
    texts.push_back("5. Mosaic");
    texts.push_back("6. Flag");

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

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            DrawPixel(i, j, deltaTime, currentModifier.first, currentModifier.second);
        }
    }

    accumulatedTime += deltaTime;
    RenderText("Tap space to change modifier", 5, 5, 3, Pixel(255, 255, 125));
    RenderText(texts[currentModifierIndex], 5, 30, 4, Pixel(255, 255, 125));

    return true;
}

void Deformations::UpdateInput()
{
    bool changeCurrentModifier = windowManager->IsKeyPressed((int)Key::SPACE);
    if (changeCurrentModifier)
    {
        UpdateCurrentModifier();
    }
}

void Deformations::UpdateCurrentModifier()
{
    currentModifierIndex++;

    if (currentModifierIndex == modifiers.size())
    {
        currentModifierIndex = 0;
    }

    currentModifier = modifiers[currentModifierIndex];
}

void Deformations::DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier)
{
    int newX = (this->*xModifier)(x + offsetX, y + offsetY) % texWidth;
    int newY = (this->*yModifier)(x + offsetX, y + offsetY) % texHeight;

    pixels[y * width + x] = texture[newY * texWidth + newX];
}

int Deformations::DefaultXModifier(int x, int y)
{
    return x;
}

int Deformations::DefaultYModifier(int x, int y)
{
    return y;
}

int Deformations::TransversalWaveXModifier(int x, int y)
{
    return x + 20 * sineTable[(y * 20 + int(accumulatedTime * 400)) % mathTableSize];
}

int Deformations::TransversalWaveYModifier(int x, int y)
{
    return y + 20 * sineTable[(x * 20 + int(accumulatedTime * 400)) % mathTableSize];
}

int Deformations::LongitudinalWaveXModifier(int x, int y)
{
    return x + 20 * sineTable[(x * 20 + int(accumulatedTime * 400)) % mathTableSize];
}

int Deformations::LongitudinalWaveYModifier(int x, int y)
{
    return y + 20 * sineTable[(y * 20 + int(accumulatedTime * 400)) % mathTableSize];
}

int Deformations::FlagXModifier(int x, int y)
{
    return x + 100 * sineTable[(y + int(accumulatedTime * 600)) % mathTableSize];
}

int Deformations::FlagYModifier(int x, int y)
{
    return y + 100 * sineTable[(x + int(accumulatedTime * 600)) % mathTableSize];
}