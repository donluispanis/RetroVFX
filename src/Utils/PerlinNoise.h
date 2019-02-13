#pragma once

class PerlinNoise
{
  public:
    PerlinNoise(int levels);
    ~PerlinNoise();

    void Build(float *&noiseMap, int &size);

  private:
    void BuildRandomMap();
    void ClearNoiseMap();
    void AddNoiseValue(int frequency, float intensity);
    void DivideNoiseMap(float divisor);

    int levels;
    float *noiseMap, *randomMap;
};