#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../ClassicDemoTemplate/Pixel.h"

class FireDemo : public ClassicDemoTemplate
{

  public:
    FireDemo(){};
    virtual ~FireDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    struct ColourStamp;

    void updateFireBase();
    void updateFireScreen();
    void updateFireInput();

    Pixel *pixels;
    int width, height;

    unsigned char *screenMapping;
    Pixel *colourMap;
    int colourMapSize = 256;
};