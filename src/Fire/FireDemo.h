#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/ColourStamp.h"

struct Pixel;
struct IWindowManager;

class FireDemo : public ClassicDemoTemplate
{
  public:
    FireDemo(){};
    virtual ~FireDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitialiseFireColours();
    void UpdateFireBase();
    void UpdateFireScreen();
    void UpdateInput();
    void SwitchColour();

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;

    unsigned char *screenMapping;
    Pixel *colourMap;
    int colourMapSize = 256;

    std::vector<std::vector<ColourStamp>> colours;
    unsigned int currentColour;
    bool isSpaceHeld;
};