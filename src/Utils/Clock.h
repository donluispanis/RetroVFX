#pragma once

#include <ctime>

class Clock
{
  public:
    Clock();
    void Reset();
    double GetElapsedTime();

  private:
    std::clock_t oldTimePoint = std::clock();
};