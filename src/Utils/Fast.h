#pragma once

class Fast
{
  public:
    static unsigned long Rand();
    static float* GenerateSineTable(int size);
    static float* GenerateCosineTable(int size);
    static const float PI;
};