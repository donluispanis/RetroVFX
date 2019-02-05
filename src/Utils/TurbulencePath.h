#pragma once

#include <vector>

class TurbulencePath
{
  public:
    TurbulencePath(float* sineTable, float *cosineTable, int mathTableSize);
    void CreateTurbulencePath(float pathVelocity, int pathRadius, int pathComplexity);
    void UpdateTurbulencePath(float deltaTime, float &pathX, float &pathY);

  private:
    struct Path
    {
        int radius;
        int phase;
        int direction;
        float advance;
    };

    float pathVelocity;
    int pathRadius;
    int pathComplexity;

    float *sineTable;
    float *cosineTable;
    int mathTableSize;

    std::vector<Path> paths;
};