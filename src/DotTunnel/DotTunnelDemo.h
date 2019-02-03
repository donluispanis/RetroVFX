#pragma once

#include <deque>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "Circle.h"

struct Pixel;
struct IWindowManager;
class TurbulencePath;

class DotTunnelDemo : public ClassicDemoTemplate
{
  public:
    DotTunnelDemo(){};
    virtual ~DotTunnelDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void InitWindowManagerData();
    void InitDefaultCircleData();
    void InitMathTables();
    void InitTurbulencePath();
    void InitColourMap();
    void InitInput();
    void AddCircle();
    void UpdateCircleQueue(float deltaTime);
    void UpdateInput(float deltaTime);
    void UpdatePositionFromInput(float deltaTime);
    void UpdateVelocityFromInput(float deltaTime);
    void UpdateDotSizeFromInput(float deltaTime);
    void PopulateCircleQueue();
    void DrawCircle(const Circle &c);
    float CalculateOpacity(const float radius);
    void UpdateCircle(Circle &c, float deltaTime);
    void EraseCircle(const Circle &circle);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    float *sineTable, *cosineTable;
    int mathTableSize;

    std::deque<Circle> circles;
    int circleCount;
    Circle defaultCircle;
    int maxCircleRadius;
    int dotSize;
    int circlesGapDistance;

    float pathX, pathY;
    TurbulencePath *turbulencePath;

    float radiusVelocity;
    float rotationVelocity;
    float defaultRotationVelocity;

    int colourMapSize;
    Pixel *colourMap;
    int currentColour; 
};