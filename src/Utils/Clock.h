#pragma once

#include <chrono>

using TimePoint = std::chrono::steady_clock::time_point;
using SteadyClock = std::chrono::steady_clock;
using Duration = std::chrono::duration<double>;

class Clock
{
  public:
    Clock();
    void Reset();
    double GetElapsedTime();

  private:
    TimePoint oldTimePoint = SteadyClock::now();
};