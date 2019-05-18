#include "Imp_Includes.h"
#include "Imp_Music.cpp"

void UpdateNotes(long int currentCount);
float GetLeftValue();
float GetRightValue();

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

        UpdateNotes(currentCount);

        *out++ = GetLeftValue();  /* left */
        *out++ = GetRightValue(); /* rigth */
    }
    return 0;
}

void UpdateNotes(long int currentCount)
{
    for (auto& note : notes)
    {
        note.resultingSound = note.generateWave(note.frequency, currentCount) * note.currentEnvelopeValue * note.volume;
    }
}

float GetLeftValue()
{
    float sum = 0.f;

    for (auto& note : notes)
    {
        float leftAmplitude = 1.f;
        if (note.position > 0.5f)
        {
            leftAmplitude -= (note.position - 0.5f) * 2.f;
        }

        sum += note.resultingSound * leftAmplitude;
    }

    return sum;
}

float GetRightValue()
{
    float sum = 0.f;

    for (auto& note : notes)
    {
        float rightAmplitude = 1.f;
        if (note.position < 0.5f)
        {
            rightAmplitude -= (0.5f - note.position) * 2.f;
        }

        sum += note.resultingSound * rightAmplitude;
    }

    return sum;
}

void UpdateEnvelopes(float deltaTime)
{
    for (auto& note : notes)
    {
        Envelope env = note.envelope;
        note.lifetime += deltaTime;

        float life = note.lifetime;

        if (life < env.attack)
        {
            note.currentEnvelopeValue = env.peakAmplitude * (life / env.attack);
        }
        else if (life < env.attack + env.decay)
        {
            float t = (life - env.attack) / env.decay;
            note.currentEnvelopeValue = t * env.peakAmplitude + (1 - t) * env.sustainAmplitude;
        }
        else if (life < env.attack + env.decay + env.sustain)
        {
            note.currentEnvelopeValue = env.sustainAmplitude;
        }
        else if (life < env.attack + env.decay + env.sustain + env.release)
        {
            note.currentEnvelopeValue = (((env.attack + env.decay + env.sustain + env.release) - life) / env.release) * env.sustainAmplitude;
        }
        else
        {
            note.currentEnvelopeValue = -1.f;
        }
    }
}

void RemoveDeadNotes()
{
    for (unsigned int i = 0; i < notes.size(); i++)
    {
        if(notes[i].currentEnvelopeValue < 0.f)
        {
            notes.erase(notes.begin() + i);
            i--;
        }
    }
}

float GetSquaredWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    if (currentCount % steps < steps * 0.5)
    {
        return 1.f;
    }
    return -1.f;
}

float GetSawtoothWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    float percentage = currentCount % steps / float(steps);
    return percentage * 2 - 1.f;
}

float GetTriangleWaveValue(float frequency, long int currentCount)
{
    int steps = SAMPLE_RATE / frequency;
    float percentage = currentCount % steps / float(steps);
    if (percentage < 0.5f)
    {
        return percentage * 4 - 2.f;
    }
    return (1 - percentage) * 4 - 2.f;
}

float GetSineWaveValue(float frequency, long int currentCount)
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