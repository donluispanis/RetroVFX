#pragma once

class PerlinNoise2D
{
  public:
    PerlinNoise2D(int levels);
    ~PerlinNoise2D();

    void Build(float *&noiseMap, int &size);

  private:
    void BuildRandomMap();
    void ClearNoiseMap();
    void AddNoiseValue(int frequency, float intensity);
    void DivideNoiseMap(float divisor);

    int levels;
    int noiseMapSize;
    float *noiseMap, *randomMap;
};