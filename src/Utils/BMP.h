#pragma once

struct Pixel;

class BMP
{
  public:
    static void OpenRGBImage(const char *path, Pixel *&image, int &width, int &height);
    static void CloseRGBImage(Pixel *image);

  private:
    static int CharToInt(unsigned char *p);
};