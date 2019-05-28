#include "../../Utils/ColourStampGradients.h"
#include "../../ClassicDemoTemplate/Characters/Characters.h"
#include "Imp_Includes.h"

void FinalDemo::InitFire()
{
    screenMapping = new unsigned char[width * height];
    fireMapping = new unsigned char[width * height];
    colourMap = new Pixel[colourMapSize];

    for (int i = 0, n = width * height; i < n; i++)
    {
        fireMapping[i] = 0;
    }

    ColourStamp::GenerateGradient(ColourStampGradients::FIRE, colourMap, colourMapSize);
}

void FinalDemo::CloseFire()
{
    delete screenMapping;
    delete fireMapping;
    delete colourMap;
}

void FinalDemo::UpdateFire(float deltaTime)
{
    static float bigFireSize = 0;

    if(accumulatedTime < 1.25f + START_FIRE)
    {
        InitBigFireText(bigFireSize, 0);
        bigFireSize += deltaTime * 20;
    }
    if(accumulatedTime > 2.f + START_FIRE)
    {
        InitSmallFireText(8, 1);
    }
    if(accumulatedTime > 4.f + START_FIRE)
    {
        for(int i = 0; i < 256; i++)
        {
            colourMap[i].R *= 0.95;
            colourMap[i].G *= 0.95;
            colourMap[i].B *= 0.95;
        }
    }

    InitBigFireText(bigFireSize, 1);

    DrawBigFireText();
    DrawSmallFireText();
}

void FinalDemo::InitBigFireText(int size, int value)
{
    bigFireScale = size;
    bigFireHeight = height * 0.4;
    bigFireCharCount = 7;
    bigFireCharSize = bigFireScale * 6;
    bigFireTextStart = width / 2 - bigFireCharSize * (bigFireCharCount * 0.5f);

    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 0, bigFireHeight, 'C', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 1, bigFireHeight, 'P', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 2, bigFireHeight, 'U', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 3, bigFireHeight, '-', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 4, bigFireHeight, 'T', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 5, bigFireHeight, '-', bigFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, bigFireTextStart + bigFireCharSize * 6, bigFireHeight, 'U', bigFireScale);
}

void FinalDemo::InitSmallFireText(int size, int value)
{
    smallFireScale = size;
    smallFireHeight = height * 0.7;
    smallFireCharCount = 15;
    smallFireCharSize = smallFireScale * 6;
    smallFireTextStart = width / 2 - smallFireCharSize * (smallFireCharCount * 0.5f);

    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 0, smallFireHeight, 'B', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 1, smallFireHeight, 'Y', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 3, smallFireHeight, 'D', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 4, smallFireHeight, 'O', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 5, smallFireHeight, 'N', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 6, smallFireHeight, 'L', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 7, smallFireHeight, 'U', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 8, smallFireHeight, 'I', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 9, smallFireHeight, 'S', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 10, smallFireHeight, 'P', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 11, smallFireHeight, 'A', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 12, smallFireHeight, 'N', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 13, smallFireHeight, 'I', smallFireScale);
    DrawCharacterOnFireMap(fireMapping, width, value, smallFireTextStart + smallFireCharSize * 14, smallFireHeight, 'S', smallFireScale);
}

void FinalDemo::DrawBigFireText()
{
    int initialX = width * 0.5f - bigFireCharSize * (bigFireCharCount * 0.5f);
    int initialY = bigFireHeight - bigFireCharSize;
    int finalX = width * 0.5f + bigFireCharSize * (bigFireCharCount);
    int finalY = bigFireHeight + bigFireCharSize;

    for (int j = finalY; j >= initialY; j--)
    {
        for (int i = initialX - bigFireCharSize; i < finalX; i++)
        {
            int index = j * width + i;
            int rowBelow = index + width;

            if (fireMapping[rowBelow] != 0)
            {
                screenMapping[rowBelow] = 255;
            }

            int colourIndex = (screenMapping[rowBelow + 1] + screenMapping[rowBelow] + screenMapping[rowBelow - 1]) / (3.2) + (Fast::Rand() % 3 == 0 ? 2 : 0);
            screenMapping[index] = colourIndex;
            pixels[j * width + i] = colourMap[colourIndex];
        }
    }
}

void FinalDemo::DrawSmallFireText()
{
    int initialX = width * 0.5f - smallFireCharSize * (smallFireCharCount * 0.5f);
    int initialY = smallFireHeight - smallFireCharSize;
    int finalX = width * 0.5f + smallFireCharSize * (smallFireCharCount * 0.5f);
    int finalY = smallFireHeight + smallFireCharSize;

    for (int j = finalY; j >= initialY; j--)
    {
        for (int i = initialX - smallFireCharSize; i < finalX; i++)
        {
            int index = j * width + i;
            int rowBelow = index + width;

            if (fireMapping[rowBelow] != 0)
            {
                screenMapping[rowBelow] = 255;
            }

            int colourIndex = (screenMapping[rowBelow + 1] + screenMapping[rowBelow] + screenMapping[rowBelow - 1]) / (3.5) + (Fast::Rand() % 3 == 0 ? 3 : 0);
            screenMapping[index] = colourIndex;
            pixels[j * width + i] = colourMap[colourIndex];
        }
    }
}

void FinalDemo::DrawCharacterOnFireMap(unsigned char *map, int width, unsigned char value, int x, int y, char character, int scale)
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
                map[j * width + i] = value;
            }
        }
    }
}