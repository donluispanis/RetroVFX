#pragma once

#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;

class Clock
{
  public:
    Clock();
    void Reset();
    double GetElapsedTime();

  private:
    TimePoint oldTimePoint;
};