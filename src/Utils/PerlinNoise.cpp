#include "PerlinNoise.h"
#include "Fast.h"
#include <cmath>
#include <climits>

PerlinNoise::PerlinNoise(int levels)
{
    this->levels = pow(2, levels);
    noiseMap = new float[this->levels];
    randomMap = new float[this->levels];

    BuildRandomMap();
    ClearNoiseMap();
}

PerlinNoise::~PerlinNoise()
{
    delete[] noiseMap;
    delete[] randomMap;
}

void PerlinNoise::Build(float *&outNoiseMap, int &outSize)
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

void PerlinNoise::BuildRandomMap()
{
    for (int i = 0; i < levels; i++)
    {
        randomMap[i] = Fast::Rand() / float(ULONG_MAX);
    }
}

void PerlinNoise::ClearNoiseMap()
{
    for (int i = 0; i < levels; i++)
    {
        noiseMap[i] = 0.f;
    }
}

void PerlinNoise::AddNoiseValue(int frequency, float intensity)
{
    for (int i = 0; i < levels; i += frequency)
    {
        for (int j = 0; j < levels; j++)
        {
            float currentValue = randomMap[j / frequency];
            float nextValue = randomMap[((j / frequency + 1) * frequency) % levels];

            int path = ((j % frequency) / float(frequency));

            noiseMap[j] += (currentValue * (j - path) + nextValue * path) * intensity;
        }
    }
}

void PerlinNoise::DivideNoiseMap(float divisor)
{
    for (int i = 0; i < levels; i++)
    {
        noiseMap[i] /= divisor;
    }
}