#include "Clock.h"

Clock::Clock()
{
    Reset();
}

void Clock::Reset()
{
    oldTimePoint = std::chrono::system_clock::now();
}

double Clock::GetElapsedTime()
{
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - oldTimePoint;
    return elapsed_seconds.count();
}