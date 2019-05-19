#include "Imp_Includes.h"

void FinalDemo::InitPlasma()
{
    sineTable = Fast::GenerateSineTable(mathTableSize);

    plasmaColourMap = new Pixel[plasmaColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::PLASMA, plasmaColourMap, plasmaColourMapSize);

    lavaColourMap = new Pixel[plasmaColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::FIRE, lavaColourMap, plasmaColourMapSize);
}

void FinalDemo::ClosePlasma()
{
    delete[] plasmaColourMap;
    delete[] lavaColourMap;
    Fast::DeleteMathTable(sineTable);
}

void FinalDemo::UpdatePlasma(float deltaTime)
{
    static const int textSize = 30;
    static const int scale = 5;

    if (accumulatedTime < START_PLASMA + 10.f)
    {
        static float opacity = 1.f;

        if (accumulatedTime > START_PLASMA + 9.f)
        {
            opacity -= deltaTime;
        }

        RenderText("did you", 25, 67, textSize, Pixel(255) * opacity);
        RenderText("ask for", 25, 284, textSize, Pixel(255) * opacity);
        RenderText("plasma?", 40, 500, textSize, Pixel(255) * opacity);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (pixels[j * width + i] == Pixel(255))
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

                    pixels[j * width + i] = plasmaColourMap[index];
                }
            }
        }
    }
    else
    {
        static float opacity = 0.f;
        static float textOpacity = 0.f;

        if (opacity < 1.f)
        {
            opacity += deltaTime * 0.1f;
        }
        else
        {
            opacity = 1.f;
        }

        if (textOpacity < 1.f)
        {
            textOpacity += deltaTime;
        }

        RenderText("did you", 25, 67, textSize, Pixel(125, 125, 124) * textOpacity);
        RenderText(" meant ", 25, 284, textSize, Pixel(125, 125, 124) * textOpacity);
        RenderText(" lava? ", 40, 500, textSize, Pixel(125, 125, 124) * textOpacity);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (pixels[j * width + i] != Pixel(125, 125, 124) * textOpacity)
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

                    pixels[j * width + i] = lavaColourMap[index] * opacity;
                }
            }
        }
    }
}