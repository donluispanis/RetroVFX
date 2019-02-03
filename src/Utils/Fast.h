#pragma once

class Fast
{
  public:
    static unsigned long Rand();
    static float* GenerateSineTable(float* sineTable, int size);
    static float* GenerateCosineTable(float* cosineTable, int size);
    static const float PI;
};