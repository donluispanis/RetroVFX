#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../ClassicDemoTemplate/Characters/Characters.h"
#include "../Utils/Fast.h"
#include <string>

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    cosineTable = Fast::GenerateCosineTable(mathTableSize);
    sineTable = Fast::GenerateSineTable(mathTableSize);

    fire.InitFire(width, height, pixels);
    geometry.InitGeometry(width, height, this);
    plasma.InitPlasma(width, height, pixels, this, cosineTable, sineTable);
    planes.InitPlanes(width, height, pixels, this);
    ending.InitEnding(width, height, this, cosineTable, sineTable);
    audio.InitAudio(START_FIRE, START_GEOMETRY, START_PLASMA, START_PLANES, START_ENDING);

    accumulatedTime = 0;

    return true;
}

bool FinalDemo::Destroy()
{
    fire.CloseFire();
    geometry.CloseGeometry();
    plasma.ClosePlasma();
    planes.ClosePlanes();
    ending.CloseEnding();
    audio.CloseAudio();

    Fast::DeleteMathTable(cosineTable);
    Fast::DeleteMathTable(sineTable);

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    if (accumulatedTime > START_FIRE && accumulatedTime < DURATION_FIRE + START_FIRE)
    {
        fire.UpdateFire(deltaTime, accumulatedTime, START_FIRE);
    }
    if (accumulatedTime > START_GEOMETRY && accumulatedTime < DURATION_GEOMETRY + START_GEOMETRY)
    {
        geometry.UpdateGeometry(deltaTime, accumulatedTime, START_GEOMETRY);
    }
    if(accumulatedTime > START_PLASMA && accumulatedTime < DURATION_PLASMA + START_PLASMA)
    {
        plasma.UpdatePlasma(deltaTime, accumulatedTime, START_PLASMA);
    }
    if(accumulatedTime > START_PLANES && accumulatedTime < DURATION_PLANES + START_PLANES)
    {
        planes.UpdatePlanes(deltaTime, accumulatedTime, START_PLANES);
    }
    if(accumulatedTime > START_ENDING && accumulatedTime < DURATION_ENDING + START_ENDING)
    {
        ending.UpdateEnding(deltaTime, accumulatedTime, START_ENDING, tunnelBeat);
    }
    if(accumulatedTime > DURATION_TOTAL)
    {
        return false;
    }

    audio.UpdateSound(deltaTime, accumulatedTime, tunnelBeat);

    return true;
}

void FinalDemo::DrawCharactersOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, const char *characters, int scale)
{
    std::string txt(characters);
    for (auto &c : txt)
    {
        c = toupper(c);
    }

    for (auto c : txt)
    {
        DrawCharacterOnMap(map, width, colour, x, y, c, scale);
        x += 6 * scale;
    }
}

void FinalDemo::DrawCharacterOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, char character, int scale)
{
    if (character < 0 || character == ' ')
    {
        return;
    }

    const char *c = Characters::GetCharactersMap()[character];

    for (int i = x; i < x + 5 * scale; i++)
    {
        for (int j = y; j < y + 5 * scale; j++)
        {
            if(scale <= 0.f)
            {
                scale = 0.001f;
            }

            int offsetX = (i - x) / scale;
            int offsetY = (j - y) / scale;

            if (c[offsetY * 5 + offsetX] != ' ')
            {
                map[j * width + i] = colour;
            }
        }
    }
}