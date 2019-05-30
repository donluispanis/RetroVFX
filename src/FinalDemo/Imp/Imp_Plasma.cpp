#include "Imp_Plasma.h"
#include "../../Utils/Fast.h"
#include "../../Utils/ColourStamp.h"
#include "../../Utils/ColourStampGradients.h"
#include "../FinalDemo.h"

void Imp_Plasma::InitPlasma(int width, int height, Pixel *pixels, FinalDemo *engine, float *cosTable, float *sinTable)
{
    this->width = width;
    this->height = height;
    this->pixels = pixels;
    this->engine = engine;
    this->cosineTable = cosTable;
    this->sineTable = sinTable;

    plasmaColourMap = new Pixel[plasmaColourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::PLASMA, plasmaColourMap, plasmaColourMapSize);

    plasmaTexture = new Pixel[(width / 2) * (height / 2)];
    for (int i = 0, n = (width / 2) * (height / 2); i < n; i++)
    {
        plasmaTexture[i] = Pixel(0);
    }

    plasmaDisplacement.X = width / 2;
    plasmaDisplacement.Y = height / 2;
}

void Imp_Plasma::ClosePlasma()
{
    delete[] plasmaColourMap;
    delete[] plasmaTexture;
}

void Imp_Plasma::UpdatePlasma(float deltaTime, float accumulatedTime, float startTime)
{
    static const int textSize = 15;
    static const int scale = 5;

    static float t = 0.f;
    static Pixel textColour = Pixel(255);

    engine->DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 12, 34, "did you", textSize);
    engine->DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 12, 142, "ask for", textSize);
    engine->DrawCharactersOnMap(plasmaTexture, width / 2, textColour, 20, 250, "plasma?", textSize);

    if (accumulatedTime > startTime + 4.f)
    {
        static bool clearScreen = false;
        static float opacity = 1.f;

        opacity -= deltaTime * 0.5f;
        if (opacity < 0.f)
        {
            opacity = 0.f;
        }

        if (!clearScreen)
        {
            clearScreen = true;
            engine->ClearScreen(Pixel());
        }

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
                    plasmaTexture[j * nw + i] = c + Pixel(255) * opacity;
                }
            }
        }
    }

    static const int plasmaTexWidth = width / 2;
    static const int plasmaTexHeight = height / 2;
    static float amplitude = 0.f;
    static float scaleModifier = 0.5f;
    static float fColour = 0.f;

    for (int j = 0, nh = height; j < nh; j += 2)
    {
        int aux = (j + (int)plasmaDisplacement.Y) * width;
        int aux1 = (j + 1 + (int)plasmaDisplacement.Y) * width;
        for (int i = 0, nw = width; i < nw; i += 2)
        {
            if (accumulatedTime < startTime + 6.f)
            {
                float sine = sineTable[plasmaAngle % mathTableSize];
                float cosine = cosineTable[plasmaAngle % mathTableSize];

                if (plasmaScale <= 0.f)
                {
                    plasmaScale = 0.001f;
                }

                int texX = Fast::Abs(int((i * cosine - j * sine) / plasmaScale));
                int texY = Fast::Abs(int((j * cosine + i * sine) / plasmaScale));

                if (engine->IsPixelOutOfBounds(i + plasmaDisplacement.X + 1, j + plasmaDisplacement.Y + 1))
                {
                    continue;
                }

                if (texX < 0 || texX >= plasmaTexWidth || texY < 0 || texY >= plasmaTexHeight)
                {
                    continue;
                }

                const Pixel colour = plasmaTexture[texY * plasmaTexWidth + texX];
                pixels[aux + i + (int)plasmaDisplacement.X] = colour;
                pixels[aux + i + 1 + (int)plasmaDisplacement.X] = colour;
                pixels[aux1 + i + (int)plasmaDisplacement.X] = colour;
                pixels[aux1 + i + 1 + (int)plasmaDisplacement.X] = colour;
            }
            else
            {
                int newX = int(i * 0.5f + amplitude * sineTable[int(j * 0.5f + int(accumulatedTime * 300)) % mathTableSize]);
                int newY = int(j * 0.5f + amplitude * sineTable[int(i * 0.5f + int(accumulatedTime * 300)) % mathTableSize]);

                float sine = sineTable[plasmaAngle % mathTableSize];
                float cosine = cosineTable[plasmaAngle % mathTableSize];

                float auxScale = plasmaScale * scaleModifier;

                if (auxScale <= 0.f)
                {
                    auxScale = 0.001f;
                }

                int texX = Fast::Abs(int((newX * cosine - newY * sine) / auxScale + width) % plasmaTexWidth);
                int texY = Fast::Abs(int((newY * cosine + newX * sine) / auxScale + height) % plasmaTexHeight);

                const Pixel colour = plasmaTexture[texY * plasmaTexWidth + texX] + Pixel(fColour);

                pixels[aux + i] = colour;
                pixels[aux + i + 1] = colour;
                pixels[aux1 + i] = colour;
                pixels[aux1 + i + 1] = colour;
            }
        }
    }

    if (plasmaScale < 2.f)
    {
        plasmaScale += deltaTime * 0.5;
        plasmaDisplacement.X -= deltaTime * plasmaTexWidth * 0.25f;
        plasmaDisplacement.Y -= deltaTime * plasmaTexHeight * 0.25f;
        if (plasmaDisplacement.X < 0.f)
        {
            plasmaDisplacement.X = 0.f;
        }
        if (plasmaDisplacement.Y < 0.f)
        {
            plasmaDisplacement.Y = 0.f;
        }
    }

    if (accumulatedTime > startTime + 6.f && amplitude < 50.f)
    {
        amplitude += deltaTime * 20;
    }
    if (accumulatedTime > startTime + 13.f)
    {
        plasmaAngle += deltaTime * 200;
        scaleModifier *= 0.992f;
    }
    if (accumulatedTime >= startTime + 28.f)
    {
        fColour += 255.f * deltaTime * 0.5;
        if (fColour > 255.f)
            if (fColour > 255.f)
            {
                fColour = 255.f;
            }
    }
}