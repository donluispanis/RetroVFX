#include "Imp_Includes.h"

void FinalDemo::InitPlasma()
{
    sineTable = Fast::GenerateSineTable(mathTableSize);

    plasmaColourMap = new Pixel[plasmaColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::PLASMA, plasmaColourMap, plasmaColourMapSize);

    lavaColourMap = new Pixel[plasmaColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::FIRE, lavaColourMap, plasmaColourMapSize);

    plasmaTexture = new Pixel[(width / 2) * (height / 2)];
    for (int i = 0, n = (width / 2) * (height / 2); i < n; i++)
    {
        plasmaTexture[i] = Pixel(0);
    }
}

void FinalDemo::ClosePlasma()
{
    delete[] plasmaColourMap;
    delete[] lavaColourMap;
    Fast::DeleteMathTable(sineTable);
}
#include <iostream>

void FinalDemo::UpdatePlasma(float deltaTime)
{
    static const int textSize = 15;
    static const int scale = 5;

    if (accumulatedTime < START_PLASMA + 10.f)
    {
        static float t = 0.f;
        static Pixel textColour = Pixel(255);

        if (accumulatedTime > START_PLASMA + 9.f)
        {
            t += deltaTime;

            if (t > 1.f)
            {
                t = 1.f;
            }
        }

        DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 12, 34, "did you", textSize);
        DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 12, 142, "ask for", textSize);
        DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 20, 250, "plasma?", textSize);
        for (int j = 0, nh = height / 2; j < nh; j++)
        {
            for (int i = 0, nw = width / 2; i < nw; i++)
            {
                if (plasmaTexture[j * nw + i] == textColour)
                {
                    float value = 0;
                    int width_i = width - i * 2;
                    int height_j = height - j * 2;

                    value += sineTable[int((j * i) / (j + i + 1) * scale + accumulatedTime * 191) % mathTableSize];
                    value += sineTable[int((width_i * j) / (width_i + j + 1) * scale + accumulatedTime * 157) % mathTableSize];
                    value += sineTable[int((width_i * height_j) / (width_i + height_j + 1) * scale + accumulatedTime * 113) % mathTableSize];
                    value += sineTable[int((i * height_j) / (i + height_j + 1) * scale + accumulatedTime * 67) % mathTableSize];
                    value *= 0.25f;

                    int index = Fast::Abs((int)(value * (plasmaColourMapSize - 1)));
                    Pixel c = plasmaColourMap[index] * (1.f - t) + textColour * t;
                    plasmaTexture[j * nw + i] = c;
                }
            }
        }

        for (int j = 0, nh = height; j < nh; j += 2)
        {
            int aux = j * width;
            int aux1 = (j + 1) * width;
            for (int i = 0, nw = width; i < nw; i += 2)
            {
                const Pixel colour = plasmaTexture[(j / 2) * (width / 2) + i / 2];
                pixels[aux + i] = colour;
                pixels[aux + i + 1] = colour;
                pixels[aux1 + i] = colour;
                pixels[aux1 + i + 1] = colour;
            }
        }
    }
    else
    {
        static float opacity = 0.f;
        static Pixel textColour = Pixel(255, 254, 253);
        static bool clearScreen = false;

        if (!clearScreen)
        {
            ClearScreen(Pixel(0));
            clearScreen = true;
        }

        if (opacity < 0.8f)
        {
            opacity += deltaTime * 0.1f;
        }

        RenderText("did you", 24, 68, textSize * 2, textColour);
        RenderText(" mean ", 100, 284, textSize * 2, textColour);
        RenderText(" lava? ", 40, 500, textSize * 2, textColour);

        static Pixel fadeOut(0);
        if (accumulatedTime > START_PLASMA + 20.f)
        {
            static float accumulator = 0.f;
            accumulator += deltaTime;
            fadeOut = Pixel(accumulator * 50);
        }

        for (int j = 0; j < height; j += 2)
        {
            for (int i = 0; i < width; i += 2)
            {
                if (pixels[j * width + i] != textColour)
                {
                    float value = 0;
                    int width_i = width - i;
                    int height_j = height - j;

                    value += sineTable[int((j * i) / (j + i + 1) * scale + accumulatedTime * 191) % mathTableSize];
                    value += sineTable[int((width_i * j) / (width_i + j + 1) * scale + accumulatedTime * 157) % mathTableSize];
                    value += sineTable[int((width_i * height_j) / (width_i + height_j + 1) * scale + accumulatedTime * 113) % mathTableSize];
                    value += sineTable[int((i * height_j) / (i + height_j + 1) * scale + accumulatedTime * 67) % mathTableSize];
                    value *= 0.25f;

                    int index = Fast::Abs((int)(value * (plasmaColourMapSize - 1)));

                    const Pixel colour = lavaColourMap[index] * opacity;
                    const int height1 = j * width + i;
                    const int height2 = (j + 1) * width + i;

                    Pixel colour1 = colour + fadeOut;
                    pixels[height1] = colour1;
                    pixels[height1 + 1] = colour1;
                    pixels[height2] = colour1;
                    pixels[height2 + 1] = colour1;
                }
            }
        }
    }
}