#include "Imp_Includes.h"

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData)
{
    float *out = (float *)outputBuffer;
    static long int currentCount = 0;

    for (unsigned long i = 0; i < framesPerBuffer; i++)
    {
        currentCount++;

        *out++ = 0; /* left */
        *out++ = 0; /* rigth */
    }
    return 0;
}

void FinalDemo::InitAudio()
{
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, 0);
    Pa_StartStream(stream);
}

void FinalDemo::CloseAudio()
{
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}

float GetSquaredWaveValue(int frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    if (currentCount % steps < steps * 0.5)
    {
        return 1.f;
    }
    return -1.f;
}

float GetSawtoothWaveValue(int frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    float percentage = currentCount % steps / float(steps);
    return percentage * 2 - 1.f;
}

float GetTriangleWaveValue(int frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    float percentage = currentCount % steps / float(steps);
    if (percentage < 0.5f)
    {
        return percentage * 4 - 2.f;
    }
    return (1 - percentage) * 4 - 2.f;
}

float GetSineWaveValue(int frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    float percentage = currentCount % steps / float(steps);
    return sin(2 * Fast::PI * percentage);
}

float GetNoiseValue()
{
    return (Fast::Rand() / float(ULONG_MAX)) * 2 - 1;
}

float GetLowPassNoiseValue(float intensity)
{
    static float oldValue = 0;
    float newValue = intensity * GetNoiseValue() + (1 - intensity) * oldValue;
    oldValue = newValue;
    return newValue;
}