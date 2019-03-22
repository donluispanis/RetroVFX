#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Object3D.h"

struct Pixel;
struct IWindowManager;

class FinalDemo : public ClassicDemoTemplate
{
  public:
    FinalDemo(){};
    virtual ~FinalDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void GeneratePerspectiveProjection(Object3D &object);

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;
};