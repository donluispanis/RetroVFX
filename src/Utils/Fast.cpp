#include "Fast.h"
#include <cmath>

const float Fast::PI = 3.14159265358979323846;

unsigned long Fast::Rand()
{
    static unsigned long x = 123456789, y = 362436069, z = 521288629;
    static unsigned long t;

    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

int Fast::Abs(int n)
{
    if (n < 0)
        return n * -1;
    return n;
}

float Fast::Abs(float n)
{
    if (n < 0.f)
        return n * -1.f;
    return n;
}

float *Fast::GenerateSineTable(int size)
{
    float* sineTable = new float[size];

    for (int i = 0; i < size; i++)
    {
        float value = (i * 2 * Fast::PI) / size;
        sineTable[i] = sin(value);
    }

    return sineTable;
}

float *Fast::GenerateCosineTable(int size)
{
    float *cosineTable = new float[size];

    for (int i = 0; i < size; i++)
    {
        float value = (i * 2 * Fast::PI) / size;
        cosineTable[i] = cos(value);
    }

    return cosineTable;
}

void Fast::DeleteMathTable(float * table)
{
    delete [] table;
}