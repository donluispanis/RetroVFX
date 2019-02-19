#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/ColourStamp.h"

struct Pixel;
struct IWindowManager;

class GeometryDemo : public ClassicDemoTemplate
{
  public:
    GeometryDemo(){};
    virtual ~GeometryDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitInput();
    void InitialiseFireColours();
    void UpdateFireBase();
    void UpdateFireScreen();
    void UpdateInput();
    void SwitchColour();

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;
};