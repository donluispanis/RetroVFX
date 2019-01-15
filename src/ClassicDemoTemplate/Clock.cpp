#include "Clock.h"

Clock::Clock()
{
    newTimePoint = std::chrono::system_clock::now();
    oldTimePoint = newTimePoint;
}

void Clock::Reset()
{
    oldTimePoint = newTimePoint;
    newTimePoint = std::chrono::system_clock::now();
}

double Clock::GetElapsedTime()
{
    std::chrono::duration<double> elapsed_seconds = newTimePoint - oldTimePoint;
    return elapsed_seconds.count();
}