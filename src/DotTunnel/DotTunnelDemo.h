#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;
struct Circle;
struct IWindowManager;

class DotTunnelDemo : public ClassicDemoTemplate
{
  public:
    DotTunnelDemo(){};
    virtual ~DotTunnelDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitSineTable();
    void InitCosineTable();
    void DrawCircle(const Circle &c, const Pixel &colour);
    void ClearCircle(const Circle &circle);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    float *sineTable, *cosineTable;
    int mathTableSize;
};