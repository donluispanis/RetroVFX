#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/Fast.h"

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

    void InitColours();
    void InitInput();
    void SwitchColour();
    void UpdateInput();

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;

    static constexpr int tableSize = 1024;
    static constexpr Fast::SineTable<tableSize> sine;
    static constexpr Fast::SquareRootTable<tableSize> sqrt;

    Pixel *colourMap;
    int colourMapSize;
    std::vector<std::vector<ColourStamp>> colours;
    unsigned int currentColour;

    float accumulatedTime;
    int scale;
};