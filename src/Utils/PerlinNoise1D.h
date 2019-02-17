#pragma once

class PerlinNoise1D
{
  public:
    PerlinNoise1D(int levels);
    ~PerlinNoise1D();

    void Build(float *&noiseMap, int &size);

  private:
    void BuildRandomMap();
    void ClearNoiseMap();
    void AddNoiseValue(int frequency, float intensity);
    void DivideNoiseMap(float divisor);

    int levels;
    float *noiseMap, *randomMap;
};