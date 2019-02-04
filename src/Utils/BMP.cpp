#include "BMP.h"
#include "Pixel.h"
#include "FileLoader.h"

void BMP::LoadRGBImage(const char *path, Pixel *&image, int &width, int &height)
{
    unsigned char *imageBinary = nullptr;
    unsigned int imageSize;

    FileLoader::LoadBinaryFile(path, imageBinary, imageSize);

    int imageStart = CharToInt(imageBinary + 10);
    width = CharToInt(imageBinary + 18);
    height = CharToInt(imageBinary + 22);
    image = new Pixel[width * height];

    for (int i = imageStart, p = 0; i < imageSize; i += 3, p++)
    {
        if(i != 0 && i % (width * 3) == 0)
        {
            i += i % 4;
            continue;
        }
        image[p] = Pixel(imageBinary[i], imageBinary[i + 1], imageBinary[i + 2]);
    }
}

int BMP::CharToInt(unsigned char *p)
{
    int number = 0;

    number = p[0];
    number = number | p[1] << 8;
    number = number | p[2] << 16;
    number = number | p[3] << 24;

    return number;
}