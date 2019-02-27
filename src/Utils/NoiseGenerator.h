#pragma once

class NoiseGenerator
{
  public:
    NoiseGenerator(int width, int height, int blur);
    ~NoiseGenerator();
    float *Generate2DNoise();

  private:
    void CreateRandomMap();
    float AveragePixelValue(int i, int j);

    float *noiseMap;
    float *randomMap;
    int width, height, size;
    int blur;
    float averagingValue;
};