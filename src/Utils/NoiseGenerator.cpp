#include "NoiseGenerator.h"
#include "Fast.h"
#include <climits>

NoiseGenerator::NoiseGenerator(int width, int height, int blur)
{
    this->width = width;
    this->height = height;
    this->blur = blur;
    this->size = width * height;

    averagingValue = 1 / float(blur * blur);
    noiseMap = new float[size];
    randomMap = new float[size];
}

NoiseGenerator::~NoiseGenerator()
{
    delete[] noiseMap;
    delete[] randomMap;
}

float *NoiseGenerator::Generate2DNoise()
{
    CreateRandomMap();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            noiseMap[j * width + i] = AveragePixelValue(i, j);
        }
    }

    return noiseMap;
}

void NoiseGenerator::CreateRandomMap()
{
    for (int i = 0; i < size; i++)
    {
        randomMap[i] = (Fast::Rand() / (float)ULONG_MAX);
    }
}

float NoiseGenerator::AveragePixelValue(int x, int y)
{
    int maxX = x + blur + 1;
    int maxY = y + blur + 1;

    float sum = 0.f;
    float counter = 0.f;

    for (int i = x - blur; i < maxX; i++)
    {
        for (int j = y - blur; j < maxY; j++)
        {
            if (i >= 0 && j >= 0 && i < width && j < height)
            {
                sum += randomMap[j * width + i];
                counter++;
            }
        }
    }

    sum /= counter;

    return sum;
}