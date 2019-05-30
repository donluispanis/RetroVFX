#pragma once

#include "../../Utils/Pixel.h"
#include "../../Utils/Point2D.h"

struct FinalDemo;

class Imp_Plasma
{
public:
    void InitPlasma(int width, int height, Pixel *pixels, FinalDemo *engine, float *cosTable, float *sinTable);
    void UpdatePlasma(float deltaTime, float accumulatedTime, float startTime);
    void ClosePlasma();

private:
    void DrawText();
    void ApplyPlasmaTextureOnText(float accumulatedTime, float startTime, float deltaTime);
    void ApplyTextureScaling(int i, int j, int indexY, int indexY1);
    void ApplyTextureDeformation(int i, int j, float accumulatedTime, int indexY, int indexY1);
    void UpdateTexturePosition(float deltaTime);
    void UpdateTextureDeformation(float accumulatedTime, float startTime, float deltaTime);
    void ApplyFadeOut(float accumulatedTime, float startTime, float deltaTime);

    const int mathTableSize = 1024;
    float *sineTable;
    float *cosineTable;

    const int plasmaColourMapSize = 256;
    Pixel *plasmaColourMap;

    Pixel *plasmaTexture;

    int plasmaAngle = 0;
    float plasmaScale = 0.0001f;

    Point2D plasmaDisplacement;
    int plasmaTexWidth;
    int plasmaTexHeight;
    float amplitude = 0.f;
    float scaleModifier = 0.5f;
    float fColour = 0.f;

    const int textSize = 15;
    const int scale = 5;

    float t = 0.f;
    Pixel textColour = Pixel(255);

    int width, height;
    Pixel *pixels;
    FinalDemo *engine;
};