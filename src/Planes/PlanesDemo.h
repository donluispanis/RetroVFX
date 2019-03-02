#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Point2D.h"

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

    void RegisterInput();
    Point2D CalculateIntersectionOfTwoLinesGiven4Points(Point2D line1_1, Point2D line1_2, Point2D line2_1, Point2D line2_2);
    void UpdateInput(float deltaTime);

    int texWidth, texHeight;
    int texSize;
    Pixel *texture;

    float *sineTable, *cosineTable;
    int mathTableSize;

    Point2D cameraPosition;
    float cameraAngle;

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;
};