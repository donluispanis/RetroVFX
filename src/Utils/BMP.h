#pragma once

struct Pixel;

class BMP
{
  public:
    static void LoadRGBImage(const char *path, Pixel *&image, int &width, int &height);

  private:
    static int CharToInt(unsigned char *p);
};