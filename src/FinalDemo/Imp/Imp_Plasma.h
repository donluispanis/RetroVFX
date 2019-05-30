#pragma once

#include "../../Utils/Pixel.h"
#include "../../Utils/Point2D.h"

struct FinalDemo;

class Imp_Plasma
{
public:
    void InitPlasma(int width, int height, Pixel* pixels, FinalDemo* engine, float* cosTable, float* sinTable);
    void UpdatePlasma(float deltaTime, float accumulatedTime, float startTime);
    void ClosePlasma();

private:
    const int mathTableSize = 1024;
    float *sineTable;
    float *cosineTable;

    const int plasmaColourMapSize = 256;
    Pixel *plasmaColourMap;

    Pixel *plasmaTexture;

    int plasmaAngle = 0;
    float plasmaScale = 0.0001f;

    Point2D plasmaDisplacement;

    int width, height;
    Pixel* pixels;
    FinalDemo* engine;
};