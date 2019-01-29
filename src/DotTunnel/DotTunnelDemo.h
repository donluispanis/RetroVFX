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
    void UpdateCircleQueue(float deltaTime);
    void UpdateTunnelPath(float deltaTime);
    void PopulateCircleQueue();
    void DrawCircle(const Circle &c);
    void UpdateCircle(Circle &c, float deltaTime);
    void EraseCircle(const Circle &circle);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    float *sineTable, *cosineTable;
    int mathTableSize;

    float pathX, pathY, pathVelocity;
    int pathRadius, pathComplexity;
    int pathCirclesDistance;

    std::deque<Circle> circles;
    int circleCount;

    Circle defaultCircle;
};