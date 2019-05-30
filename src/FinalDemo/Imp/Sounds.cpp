#include "Sounds.h"
#include "../../Utils/Fast.h"
#include <cmath>
#include <climits>

float Sounds::GetSquaredWaveValue(float frequency, long int currentCount)
{
    if(frequency == 0.f || currentCount == 0)
    {
        return 0.f;
    }
    
    int steps = SAMPLE_RATE / frequency;
    if (currentCount % steps < steps * 0.5)
    {
        return 1.f;
    }
    return -1.f;
}

float Sounds::GetSawtoothWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;

    if(frequency == 0.f || currentCount == 0 || steps == 0.f)
    {
        return 0.f;
    }
    
    float percentage = currentCount % steps / float(steps);
    return percentage * 2 - 1.f;
}

float Sounds::GetTriangleWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;

    if(frequency == 0.f || currentCount == 0 || steps == 0.f)
    {
        return 0.f;
    }
    
    float percentage = currentCount % steps / float(steps);
    if (percentage < 0.5f)
    {
        return percentage * 4 - 2.f;
    }
    return (1 - percentage) * 4 - 2.f;
}

float Sounds::GetSineWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;

    if(frequency == 0.f || currentCount == 0 || steps == 0.f)
    {
        return 0.f;
    }

    float percentage = currentCount % steps / float(steps);
    return sin(2 * Fast::PI * percentage);
}

float Sounds::GetNoiseValue()
{
    return (Fast::Rand() / float(ULONG_MAX)) * 2 - 1;
}

float Sounds::GetLowPassNoiseValue(float intensity)
{
    static float oldValue = 0;
    float newValue = intensity * GetNoiseValue() + (1 - intensity) * oldValue;
    oldValue = newValue;
    return newValue;
}

float Sounds::GetHighPassNoiseValue(float intensity)
{
    static float oldValueY = 0.f;
    static float oldValueX = 0.f;
    
    float newValueX = GetNoiseValue();
    float newValueY = intensity * oldValueY + intensity * (newValueX - oldValueX);

    oldValueX = newValueX;
    oldValueY = newValueY;

    return newValueY;
}

float Sounds::CreateArmonicSound(float frequency, long int currentCount)
{
    return GetSawtoothWaveValue(frequency * 0.5f, currentCount) * 0.4f +
           GetSquaredWaveValue(frequency, currentCount) * 0.4 +
           GetSquaredWaveValue(frequency * 2.f, currentCount) * 0.15 +
           GetNoiseValue() * 0.05;
}

float Sounds::CreateSeaWavesSound(float frequency, long int currentCount)
{
    return GetLowPassNoiseValue(0.1f) *
               GetSineWaveValue(frequency, currentCount) * 0.9 +
           GetLowPassNoiseValue(0.1f) * 0.1;
}

float Sounds::CreateDrumSound(float frequency, long int currentCount)
{
    return GetNoiseValue();
}

float Sounds::CreateSynthSound(float frequency, long int currentCount)
{
    const float LFO = GetSineWaveValue(2, currentCount);
    return GetTriangleWaveValue(frequency * 1.0, currentCount) * (0.45 + 0.1 * LFO) * 0.6 +
           GetTriangleWaveValue(frequency * 1.3333, currentCount) * (0.45 + 0.1 * LFO) * 0.1 +
           GetTriangleWaveValue(frequency * 1.6666, currentCount) * (0.45 + 0.1 * LFO) * 0.1 +
           GetTriangleWaveValue(frequency * 2.0, currentCount) * (0.45 + 0.1 * LFO * 2.f) * 0.1 +
           GetTriangleWaveValue(frequency * 2.6666, currentCount) * (0.45 + 0.1 * LFO * -1.f) * 0.1 +
           GetTriangleWaveValue(frequency * 4.0, currentCount) * (0.45 + 0.1 * LFO) * 0.1 +
           GetTriangleWaveValue(frequency * 5.3333, currentCount) * (0.45 + 0.1 * LFO * 2.f) * 0.1 +
           GetTriangleWaveValue(frequency * 6.6666, currentCount) * (0.45 + 0.1 * LFO * -1.f) * 0.1;
}

float Sounds::CreateLaserSound(float frequency, long int currentCount)
{
    return (GetSawtoothWaveValue(frequency, currentCount) * 0.5f +
            GetSawtoothWaveValue(frequency, currentCount) * 0.5f * GetHighPassNoiseValue(0.05)) *
               0.5 +
           GetHighPassNoiseValue(0.05) * 0.5;
}