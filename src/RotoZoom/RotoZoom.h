#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;
struct IWindowManager;

class RotoZoom : public ClassicDemoTemplate
{
  public:
    RotoZoom(){};
    virtual ~RotoZoom(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void DrawPixel(int x, int y, int offsetX, int offsetY, int angle, float scale);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    int mathTableSize;
    float *sineTable, *cosineTable;

    int texWidth, texHeight;
    Pixel *texture;
};