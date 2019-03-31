#include "Imp_Includes.h"

struct Envelope
{
    float attack, decay, sustain, release;
    float peakAmplitude, sustainAmplitude;
};

struct Note
{
    float (*generateWave)(int frequency, long int currentCount);
    float volume = 1.f;
    float lifetime = 0.f;
    int frequency = 440;
    Envelope envelope;
    float currentEnvelopeValue = 0.f;
    float resultingSound;
    float position = 0.5f; // 0 = left, 1 = right, 0.5 = center
};

Note* notes;

void UpdateEnvelopes(float deltaTime);
void UpdateNotes(long int currentCount);
float GetLeftValue();
float GetRightValue();

float CreateArmonicSound(int frequency, long int currentCount)
{
    return GetTriangleWaveValue(frequency, currentCount) * 0.20f +
            GetTriangleWaveValue(frequency * 1.5, currentCount) * 0.15f + 
            GetTriangleWaveValue(frequency * 2, currentCount) * 0.10f +
            GetTriangleWaveValue(frequency * 2.5, currentCount) * 0.10f +
            GetTriangleWaveValue(frequency * 3, currentCount) * 0.1f +
            GetTriangleWaveValue(frequency * 4, currentCount) * 0.1f +
            GetTriangleWaveValue(frequency * 5, currentCount) * 0.1f +
            GetTriangleWaveValue(frequency * 6, currentCount) * 0.1f;
}

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
    
        *out++ = 0.f;//GetLeftValue();  /* left */
        *out++ = 0.f;//GetRightValue(); /* rigth */
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

void FinalDemo::UpdateSound(float deltaTime)
{
    static bool initialized = false;
    if(!initialized)
    {
        notes = new Note[NOTE_ARRAY_SIZE];
        Envelope env = {1.f,0.5f, 2.5f, 1.f, 1.f, 0.5f};
        Note note = {CreateArmonicSound, 1.f, 0.f, 200, env, 0.f, 0.f, 0.5f};
        notes[0] = note;
    }

    UpdateEnvelopes(deltaTime);
}

float GetLeftValue()
{
    float sum = 0.f;
    for (int i = 0; i < NOTE_ARRAY_SIZE; i++)
    {
        float leftAmplitude = 1.f;
        if (notes[i].position > 0.5f)
        {
            leftAmplitude -= (notes[i].position - 0.5f) * 2.f;
        }

        sum += notes[i].resultingSound * leftAmplitude;
    }

    return sum / float(NOTE_ARRAY_SIZE);
}

float GetRightValue()
{
    float sum = 0.f;
    for (int i = 0; i < NOTE_ARRAY_SIZE; i++)
    {
        float rightAmplitude = 1.f;
        if (notes[i].position < 0.5f)
        {
            rightAmplitude -= (0.5f - notes[i].position) * 2.f;
        }

        sum += notes[i].resultingSound * rightAmplitude;
    }

    return sum / float(NOTE_ARRAY_SIZE);
}

void UpdateNotes(long int currentCount)
{
    for (int i = 0; i < NOTE_ARRAY_SIZE; i++)
    {
        notes[i].resultingSound = notes[i].generateWave(200, currentCount);
    }
}

void UpdateEnvelopes(float deltaTime)
{
    for (int i = 0; i < NOTE_ARRAY_SIZE; i++)
    {
        Envelope env = notes[i].envelope;
        notes[i].lifetime += deltaTime;

        int life = notes[i].lifetime;

        if (life < env.attack)
        {
            notes[i].currentEnvelopeValue = env.peakAmplitude * (life / env.attack);
        }
        else if(life < env.attack + env.decay)
        {
            int t = (life - env.attack) / env.decay;
            notes[i].currentEnvelopeValue = t * env.peakAmplitude + (1 - t) * env.sustainAmplitude;
        }
        else if(life < env.attack + env.decay + env.sustain)
        {
            notes[i].currentEnvelopeValue = env.sustainAmplitude;
        }
        else if(life < env.attack + env.decay + env.sustain + env.release)
        {
            notes[i].currentEnvelopeValue = (((env.attack + env.decay + env.sustain + env.release) - life) / env.release) * env.sustainAmplitude;
        }
        else
        {
            notes[i].currentEnvelopeValue = -1.f;
        }
        
    }
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