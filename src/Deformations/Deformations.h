#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;
struct IWindowManager;

class Deformations : public ClassicDemoTemplate
{
  public:
    Deformations(){};
    virtual ~Deformations(){};

  private:
    typedef int (Deformations::*delegate)(int);

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitMath();
    void DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier);

    //Modifiers
    int DefaultXModifier(int x);
    int DefaultYModifier(int y);
    int WaveXModifier(int x);
    int WaveYModifier(int y);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;
    float accumulatedTime;

    int mathTableSize;
    float *sineTable, *cosineTable;

    int texWidth, texHeight;
    Pixel *texture;
};