#pragma once

class Fast
{
  public:
    static unsigned long Rand();
    static int Abs(int n);
    static float Abs(float n);
    static float* GenerateSineTable(float* sineTable, int size);
    static float* GenerateCosineTable(float* cosineTable, int size);
    static const float PI;
};