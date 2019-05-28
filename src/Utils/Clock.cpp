#include "Clock.h"

Clock::Clock()
{
    Reset();
}

void Clock::Reset()
{
    oldTimePoint = std::clock();
}

double Clock::GetElapsedTime()
{
    double deltaTime = (std::clock() - oldTimePoint) / (double)CLOCKS_PER_SEC;
    return deltaTime;
}