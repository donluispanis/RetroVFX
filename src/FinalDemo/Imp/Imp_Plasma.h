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
    void DrawText(Pixel &, const int &);
    void ApplyPlasmaTextureOnText(float, float, float, Pixel &, const int &, float);
    void ApplyTextureScaling(int, int, const int &, const int &, int, int);
    void ApplyTextureDeformation(int, float, int, float, float, const int &, const int &, float, int, int);
    void UpdateTexturePosition(float, const int &, const int &);
    void UpdateTextureDeformation(float, float, float &, float, float &);
    void ApplyFadeOut(float, float, float &, float);

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