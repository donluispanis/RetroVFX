#include "PerlinNoise1D.h"
#include "Fast.h"
#include <cmath>
#include <climits>

PerlinNoise1D::PerlinNoise1D(int levels)
{
    this->levels = pow(2, levels);
    noiseMap = new float[this->levels + 1];
    randomMap = new float[this->levels];

    BuildRandomMap();
    ClearNoiseMap();
}

PerlinNoise1D::~PerlinNoise1D()
{
    delete[] noiseMap;
    delete[] randomMap;
}

void PerlinNoise1D::Build(float *&outNoiseMap, int &outSize)
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
    outSize = levels + 1;
}

void PerlinNoise1D::BuildRandomMap()
{
    for (int i = 0; i < levels; i++)
    {
        randomMap[i] = Fast::Rand() / float(ULONG_MAX);
    }
}

void PerlinNoise1D::ClearNoiseMap()
{
    for (int i = 0, n = levels + 1; i < n; i++)
    {
        noiseMap[i] = 0.f;
    }
}

void PerlinNoise1D::AddNoiseValue(int frequency, float intensity)
{
    int currentIndex = 0;
    int nextIndex = frequency % levels;

    auto UpdateIndex = [&](int i) {
        int tempNextIndex = ((i / frequency + 1) * frequency) % levels;

        if (tempNextIndex != nextIndex)
        {
            currentIndex = nextIndex;
            nextIndex = tempNextIndex;
        }
    };

    for (int i = 0, n = levels + 1; i < n; i++)
    {
        UpdateIndex(i);

        float currentValue = randomMap[currentIndex];
        float nextValue = randomMap[nextIndex];

        float path = (i % frequency) / float(frequency);
        noiseMap[i] += (currentValue * (1 - path) + nextValue * path) * intensity;
    }
}

void PerlinNoise1D::DivideNoiseMap(float divisor)
{
    for (int i = 0, n = levels + 1; i < n; i++)
    {
        noiseMap[i] /= divisor;
    }
}