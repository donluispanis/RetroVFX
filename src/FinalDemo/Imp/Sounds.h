#pragma once

class Sounds
{
public:
    static float GetSquaredWaveValue(float frequency, long int currentCount);
    static float GetSawtoothWaveValue(float frequency, long int currentCount);
    static float GetTriangleWaveValue(float frequency, long int currentCount);
    static float GetSineWaveValue(float frequency, long int currentCount);
    static float GetNoiseValue();
    static float GetLowPassNoiseValue(float intensity);
    static float GetHighPassNoiseValue(float intensity);

    static float CreateArmonicSound(float frequency, long int currentCount);
    static float CreateSeaWavesSound(float frequency, long int currentCount);
    static float CreateDrumSound(float frequency, long int currentCount);
    static float CreateSynthSound(float frequency, long int currentCount);
    static float CreateLaserSound(float frequency, long int currentCount);

    static const int SAMPLE_RATE = 44100;
};
