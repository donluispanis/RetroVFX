#pragma once

struct Pixel;

class BMP
{
  public:
    static bool TryOpenImageInDifferentLocations(const char* path, Pixel*&image, int &width, int &height);
    static bool OpenRGBImage(const char *path, Pixel *&image, int &width, int &height);
    static void CloseRGBImage(Pixel *image);

  private:
    static int CharToInt(unsigned char *p);
};