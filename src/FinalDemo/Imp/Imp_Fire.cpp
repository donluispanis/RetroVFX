#include "../../Utils/ColourStampGradients.h"
#include "../../ClassicDemoTemplate/Characters/Characters.h"
#include "Imp_Includes.h"

void FinalDemo::InitFire()
{
    screenMapping = new unsigned char[width / 2 * height / 2];
    fireMapping = new unsigned char[width / 2 * height / 2];
    colourMap = new Pixel[colourMapSize];

    for (int i = 0, n = width / 2 * height / 2; i < n; i++)
    {
        fireMapping[i] = 0;
    }
    for (int i = 0, nw = width / 2; i < nw; i++)
    {
        fireMapping[(int)(400 + 25 * sin(i * 0.1f)) * nw + i] = 1;
    }
    
    ColourStamp::GenerateGradient(ColourStampGradients::FIRE, colourMap, colourMapSize);
}

void FinalDemo::CloseFire()
{
    delete screenMapping;
    delete fireMapping;
    delete colourMap;
}

void FinalDemo::UpdateFire()
{
    static int displacement = 0;
    DrawCharacterOnFireMap(fireMapping, width/2, 0, displacement, 200, 'L', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 0, displacement + 120, 200, 'U', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 0, displacement + 240, 200, 'I', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 0, displacement + 360, 200, 'S', 20);
    displacement++;
    DrawCharacterOnFireMap(fireMapping, width/2, 1, displacement, 200, 'L', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 1, displacement + 120, 200, 'U', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 1, displacement + 240, 200, 'I', 20);
    DrawCharacterOnFireMap(fireMapping, width/2, 1, displacement + 360, 200, 'S', 20);

    ClearScreen(Pixel(0));
    for (int j = height / 2 - 2; j >= 0; j--)
    {
        for (int i = 0, n = width / 2; i < n; i++)
        {
            int index = j * n + i;
            int rowBelow = index + n;

            if (fireMapping[rowBelow] != 0)
            {
                screenMapping[rowBelow] = 255;
            }

            int colourIndex = (screenMapping[rowBelow + 1] + screenMapping[rowBelow] + screenMapping[rowBelow - 1]) / (3.2) + (Fast::Rand() % 3 == 0 ? 1 : 0);
            screenMapping[index] = colourIndex;
            RenderDot(i * 2, j * 2, colourMap[colourIndex], 2);
        }
    }
}

void FinalDemo::DrawCharacterOnFireMap(unsigned char* map, int width, unsigned char value, int x, int y, char character, int scale)
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
            int offsetX = (i - x) / scale;
            int offsetY = (j - y) / scale;

            if (c[offsetY * 5 + offsetX] != ' ')
            {
                map[j * width + i] = value;
            }
        }
    }
}