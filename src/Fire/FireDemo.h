#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

struct Pixel;

class FireDemo : public ClassicDemoTemplate
{
  public:
    FireDemo(){};
    virtual ~FireDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void UpdateFireBase();
    void UpdateFireScreen();

    struct ColourStamp;

    Pixel *pixels;
    int width, height;

    unsigned char *screenMapping;
    Pixel *colourMap;
    int colourMapSize = 256;
};