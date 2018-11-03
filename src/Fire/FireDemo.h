#pragma once

#include "../ClassicDemoTemplate.h"

#include <vector>

class FireDemo : public ClassicDemoTemplate
{

  public:
    FireDemo(){};
    virtual ~FireDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    struct ColourStamp {
      float percentage;
      Pixel colour;

      ColourStamp(float perc, Pixel col) {
        if(perc > 1.0f)
          percentage = 1.0f;
        else if(perc < 0.0f)
          percentage = 0.0f;
        else
          percentage = perc;

        colour = col;
      }
    };

    void interpolateColourMap(std::vector<ColourStamp> colours);
    void updateFireBase();
    void updateFireScreen();
    void updateFireInput();

    Pixel* pixels;
    int width, height;

    unsigned char* screenMapping;
    Pixel* colourMap;

    inline unsigned long fast_rand();
};