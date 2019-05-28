#include "Clock.h"

Clock::Clock()
{
    Reset();
}

void Clock::Reset()
{
    oldTimePoint = SteadyClock::now();
}

double Clock::GetElapsedTime()
{
    Duration elapsedTime = std::chrono::duration_cast<Duration>(SteadyClock::now() - oldTimePoint);
    return elapsedTime.count();
}