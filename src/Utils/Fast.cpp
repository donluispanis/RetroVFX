#include "Fast.h"

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