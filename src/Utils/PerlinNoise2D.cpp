#include "PerlinNoise2D.h"
#include "Fast.h"
#include <cmath>
#include <climits>

PerlinNoise2D::PerlinNoise2D(int levels)
{
    this->levels = pow(2, levels);
    this->size = this->levels * this->levels;
    noiseMap = new float[this->size];
    randomMap = new float[this->size];

    BuildRandomMap();
    ClearNoiseMap();
}

PerlinNoise2D::~PerlinNoise2D()
{
    delete[] noiseMap;
    delete[] randomMap;
}

void PerlinNoise2D::BuildRandomMap()
{
    for (int i = 0; i < size; i++)
    {
        randomMap[i] = Fast::Rand() / float(ULONG_MAX);
    }
}

void PerlinNoise2D::ClearNoiseMap()
{
    for (int i = 0; i < size; i++)
    {
        noiseMap[i] = 0.f;
    }
}

void PerlinNoise2D::Build(float *&outNoiseMap, int &outSize)
{
    float globalIntensity = 0;
    for (int level = levels; level >= 1; level /= 2)
    {
        float intensity = level / float(levels);
        globalIntensity += intensity;

        AddNoiseValue(level, intensity);
    }
    DivideNoiseMap(globalIntensity);

    outNoiseMap = noiseMap;
    outSize = size;
}

void PerlinNoise2D::AddNoiseValue(int frequency, float intensity)
{
    int xCurrentIndex = 0;
    int xNextIndex = frequency % levels;
    int yCurrentIndex = 0;
    int yNextIndex = frequency % levels;

    auto UpdateIndex = [&](int i, int currentIndex, int nextIndex) {
        int tempNextIndex = ((i / frequency + 1) * frequency) % levels;

        if (tempNextIndex != nextIndex)
        {
            currentIndex = nextIndex;
            nextIndex = tempNextIndex;
        }
    };

    for (int i = 0; i < levels; i++)
    {
        for (int j = 0; j < levels; j++)
        {
            UpdateIndex(i, xCurrentIndex, xNextIndex);
            UpdateIndex(j, yCurrentIndex, yNextIndex);

            float xCurrentValueForCurrentY = randomMap[yCurrentIndex * levels + xCurrentIndex];
            float xNextValueForCurrentY = randomMap[yCurrentIndex * levels + xNextIndex];
            float xCurrentValueForNextY = randomMap[yNextIndex * levels + xCurrentIndex];
            float xNextValueForNextY = randomMap[yNextIndex * levels + xNextIndex];

            float xPath = (i % frequency) / float(frequency);
            float yPath = (j % frequency) / float(frequency);

            float xValueForCurrentY = xCurrentValueForCurrentY * (1 - xPath) + xNextValueForCurrentY * xPath;
            float xValueForNextY = xCurrentValueForNextY * (1 - xPath) + xNextValueForNextY * xPath;

            float yValue = yPath * (xValueForNextY - xValueForCurrentY) + xValueForCurrentY;
            noiseMap[j * levels + i] += yValue * intensity;
        }
    }
}

void PerlinNoise2D::DivideNoiseMap(float divisor)
{
    for (int i = 0; i < size; i++)
    {
        noiseMap[i] /= divisor;
    }
}