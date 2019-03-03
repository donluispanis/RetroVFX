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
    void UpdateInput(float deltaTime);

    int texWidth, texHeight;
    int texSize;
    Pixel *texture;

    Point2D cameraPosition;
    float cameraAngle;

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;

    float bumpLevel = 0;
    float textureScale = 20.f;
    int fieldOfView = 500;
};