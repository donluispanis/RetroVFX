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

    void RegisterInput();
    void UpdateInput(float deltaTime);

    struct Point
    {
        float X;
        float Y;
    };

    int texWidth, texHeight;
    int texSize;
    Pixel *texture;

    float *sineTable, *cosineTable;
    int mathTableSize;

    Point cameraPosition;
    float cameraAngle;
    float nearPlane, farPlane;

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;
};