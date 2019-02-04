#include "BMP.h"
#include "Pixel.h"
#include "FileLoader.h"

void BMP::OpenRGBImage(const char *path, Pixel *&image, int &width, int &height)
{
    unsigned char *imageBinary = nullptr;
    unsigned int imageSize;

    FileLoader::OpenBinaryFile(path, imageBinary, imageSize);

    width = CharToInt(imageBinary + 18); //Offset where width info is in BMP formar
    height = CharToInt(imageBinary + 22); //Offset where height info is in BMP formar
    image = new Pixel[width * height];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //The first part of the index "(imageSize - j * width * 3) + i * 3" draws the image inverted in the Y axis
            //The second part of the index "- ((width * 3) % 4) * j" add the corresponding offset (in the BMP format, all
            // rows are 32 bit aligned)
            int index = (imageSize - j * width * 3) + i * 3 - ((width * 3) % 4) * j;
            image[j * width + i] = Pixel(imageBinary[index + 2], imageBinary[index + 1], imageBinary[index]);
        }
    }

    FileLoader::CloseBinaryFile(imageBinary);
}

void BMP::CloseRGBImage(Pixel *image)
{
    delete [] image;
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