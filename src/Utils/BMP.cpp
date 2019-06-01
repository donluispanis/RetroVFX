#include "BMP.h"
#include "Pixel.h"
#include "FileLoader.h"
#include <string>

bool BMP::OpenRGBImage(const char *path, Pixel *&image, int &width, int &height)
{
    unsigned char *imageBinary = nullptr;
    unsigned int imageSize;

    if(!FileLoader::OpenBinaryFile(path, imageBinary, imageSize))
    {
        return false;
    }

    width = CharToInt(imageBinary + 18);  //Offset where width info is in BMP format
    height = CharToInt(imageBinary + 22); //Offset where height info is in BMP format
    image = new Pixel[width * height];

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            //The first part of the index "(imageSize - (j + 1) * width * 3) + i * 3" draws the image inverted in the Y axis
            //The second part of the index "- ((width * 3) % 4) * j" adds the corresponding offset (in the BMP format, all
            // rows are 32 bit aligned)
            int index = (imageSize - (j + 1) * width * 3) + i * 3 - ((width * 3) % 4) * j;
            image[j * width + i] = Pixel(imageBinary[index + 2], imageBinary[index + 1], imageBinary[index]);
        }
    }

    FileLoader::CloseBinaryFile(imageBinary);

    return true;
}

void BMP::CloseRGBImage(Pixel *image)
{
    delete[] image;
}

bool BMP::TryOpenImageInDifferentLocations(const char* path, Pixel *&image, int &width, int &height)
{
    bool couldOpenImage = false;
    std::string sPath(path);

    couldOpenImage = BMP::OpenRGBImage(sPath.c_str(), image, width, height);

    if(!couldOpenImage)
    {
        std::string aux = "../" + sPath;
        couldOpenImage = BMP::OpenRGBImage(aux.c_str(), image, width, height);
    }
    if(!couldOpenImage)
    {
        std::string aux = "../../" + sPath;
        couldOpenImage = BMP::OpenRGBImage(aux.c_str(), image, width, height);
    }
    if(!couldOpenImage)
    {
        std::string aux = "../../../" + sPath;
        couldOpenImage = BMP::OpenRGBImage(aux.c_str(), image, width, height);
    }
    if(!couldOpenImage)
    {
        return false;
    }
    return true;
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