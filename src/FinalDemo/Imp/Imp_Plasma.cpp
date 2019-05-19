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

        RenderText("did you", 24, 68, textSize, textColour);
        RenderText("ask for", 25, 284, textSize, textColour);
        RenderText("plasma?", 40, 500, textSize, textColour);

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (pixels[j * width + i] == textColour)
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

                    pixels[j * width + i] = plasmaColourMap[index] * (1.f - t) + textColour * t;
                }
            }
        }
    }
    else
    {
        static float opacity = 0.f;
        static Pixel textColour = Pixel(255,254,253);
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

        RenderText("did you", 24, 68, textSize, textColour);
        RenderText(" mean ", 100, 284, textSize, textColour);
        RenderText(" lava? ", 40, 500, textSize, textColour);

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