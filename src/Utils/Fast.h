#pragma once

class Fast
{
  public:
    static unsigned long Rand();

    static float *GenerateSqrtTable(int size);

    static int Abs(int n);

    static float Abs(float n);

    static float *GenerateSineTable(int size);

    static float *GenerateCosineTable(int size);

    static void DeleteMathTable(float *mathTable);

    static const float PI;
};