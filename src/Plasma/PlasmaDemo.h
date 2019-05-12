#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/ColourStamp.h"

struct Pixel;
struct IWindowManager;

class PlasmaDemo : public ClassicDemoTemplate
{
  public:
    PlasmaDemo(){};
    virtual ~PlasmaDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitMath();
    void InitColours();
    void InitInput();
    void SwitchColour();
    void UpdateInput();

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;

    int mathTableSize;
    float *sineTable;

    Pixel *colourMap;
    int colourMapSize;
    std::vector<std::vector<ColourStamp>> colours;
    unsigned int currentColour;

    float accumulatedTime;
    int scale;
};