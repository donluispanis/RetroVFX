#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/ColourStamp.h"

struct Pixel;
struct IWindowManager;

class PlanesDemo : public ClassicDemoTemplate
{
  public:
    PlanesDemo(){};
    virtual ~PlanesDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;
};