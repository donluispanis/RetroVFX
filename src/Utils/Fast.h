#pragma once

#include <cmath>

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

    static constexpr float PI = 3.14159265358979323846;

    template <int size>
    struct SineTable
    {
        constexpr SineTable() : table()
        {
            for (int i = 0; i < size; i++)
            {
                float value = (i * 2 * PI) / size;
                table[i] = sin(value);
            }
        }
        int table[size];
    };

    template <int size>
    struct CosineTable
    {
        constexpr CosineTable() : table()
        {
            for (int i = 0; i < size; i++)
            {
                float value = (i * 2 * PI) / size;
                table[i] = cos(value);
            }
        }
        int table[size];
    };

    template <int size>
    struct SquareRootTable
    {
        constexpr SquareRootTable() : table()
        {
            for (int i = 0; i < size; i++)
            {
                table[i] = sqrt(i);
            }
        }
        int table[size];
    };
};