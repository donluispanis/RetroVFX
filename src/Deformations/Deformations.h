#pragma once

#include <vector>
#include <utility>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;
struct IWindowManager;

class Deformations : public ClassicDemoTemplate
{
  public:
    Deformations(){};
    virtual ~Deformations(){};

  private:
    typedef int (Deformations::*delegate)(int, int);

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitMath();
    void RegisterModifiers();
    void RegisterInput();
    void UpdateInput();
    void UpdateCurrentModifier();
    void DrawPixel(int x, int y, float deltaTime, delegate xModifier, delegate yModifier);

    //Modifiers
    int DefaultXModifier(int x, int y);
    int DefaultYModifier(int x, int y);
    int TransversalWaveXModifier(int x, int y);
    int TransversalWaveYModifier(int x, int y);
    int LongitudinalWaveXModifier(int x, int y);
    int LongitudinalWaveYModifier(int x, int y);
    int FlagXModifier(int x, int y);
    int FlagYModifier(int x, int y);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;
    float accumulatedTime;

    int mathTableSize;
    float *sineTable, *cosineTable;

    int texWidth, texHeight;
    Pixel *texture;

    std::vector<std::pair<delegate, delegate>> modifiers;
    std::pair<delegate, delegate> currentModifier;
    unsigned int currentModifierIndex;
    std::vector<const char*> texts;
};