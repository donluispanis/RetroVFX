#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;
struct IWindowManager;

class TunnelDemo : public ClassicDemoTemplate
{
  public:
    TunnelDemo(){};
    virtual ~TunnelDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void GenerateTexture();
    void GenerateTransformationTable();

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    Pixel *tunnelTexture;
    int *distanceTable;
    int *angleTable;
};