#pragma once

#include <deque>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "Circle.h"

struct Pixel;
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

    void InitCircleQueue();
    void UpdateCircleQueue();
    void DrawCircle(const Circle &c);
    void UpdateCircle(Circle &c);
    void EraseCircle(const Circle &circle);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    float *sineTable, *cosineTable;
    int mathTableSize;
    std::deque<Circle> circles;
    int circleCount;

    Circle defaultCircle;
};