#include "PerlinNoise2D.h"
#include "Fast.h"
#include <cmath>
#include <climits>

PerlinNoise2D::PerlinNoise2D(int levels)
{
    this->levels = pow(2, levels);
    noiseMapSize = this->levels * this->levels;
    noiseMap = new float[noiseMapSize];
    randomMap = new float[noiseMapSize];

    BuildRandomMap();
    ClearNoiseMap();
}

PerlinNoise2D::~PerlinNoise2D()
{
    delete[] noiseMap;
    delete[] randomMap;
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
    outSize = levels;
}

void PerlinNoise2D::BuildRandomMap()
{
    for (int i = 0; i < noiseMapSize; i++)
    {
        randomMap[i] = Fast::Rand() / float(ULONG_MAX);
    }
}

void PerlinNoise2D::ClearNoiseMap()
{
    for (int i = 0; i < noiseMapSize; i++)
    {
        noiseMap[i] = 0.f;
    }
}

void PerlinNoise2D::AddNoiseValue(int frequency, float intensity)
{
    int currentXIndex = 0;
    int nextXIndex = frequency % levels;
    int currentYIndex = 0;
    int nextYIndex = frequency % levels;

    auto UpdateIndex = [&](int i, int &currentIndex, int &nextIndex) {
        int tempNextIndex = ((i / frequency + 1) * frequency) % levels;

        if (tempNextIndex != nextIndex)
        {
            currentIndex = nextIndex;
            nextIndex = tempNextIndex;
        }
    };

    for (int i = 0, n = levels; i < n; i++)
    {
        for (int j = 0, n = levels; j < n; j++)
        {
            UpdateIndex(i, currentXIndex, nextXIndex);
            UpdateIndex(j, currentYIndex, nextYIndex);

            float currentXValue = randomMap[currentYIndex * levels + currentXIndex];
            float nextXValue = randomMap[currentYIndex * levels + nextXIndex];
            float currentYValue = randomMap[currentYIndex * levels + currentXIndex];
            float nextYValue = randomMap[nextYIndex * levels + currentXIndex];

            float pathX = (i % frequency) / float(frequency);
            float pathY = (j % frequency) / float(frequency);

            float valueX = (currentXValue * (1 - pathX) + nextXValue * pathX) * intensity;
            float valueY = (currentYValue * (1 - pathY) + nextYValue * pathY) * intensity;

            noiseMap[j * n + i] += valueX + valueY;
        }
    }
}

void PerlinNoise2D::DivideNoiseMap(float divisor)
{
    for (int i = 0; i < noiseMapSize; i++)
    {
        noiseMap[i] /= divisor;
    }
}