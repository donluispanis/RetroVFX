#include "Imp_Includes.h"

void UpdateEnvelopes(float deltaTime);
void RemoveDeadNotes();
static int audioCallback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);

//=============================================================================
//      OBJECTS
//=============================================================================
struct Envelope
{
    float attack, decay, sustain, release;
    float peakAmplitude, sustainAmplitude;
};

struct Note
{
    float (*generateWave)(float frequency, long int currentCount);
    Envelope envelope;
    float frequency = 440.f;
    float volume = 1.f;
    float position = 0.5f; // 0 = left, 1 = right, 0.5 = center
    float lifetime = 0.f;
    float currentEnvelopeValue = 0.f;
    float resultingSound;
};

std::vector<Note> notes;

//=============================================================================
//      INSTRUMENTS
//=============================================================================
float CreateArmonicSound(float frequency, long int currentCount)
{
    return GetSawtoothWaveValue(frequency * 0.5f, currentCount) * 0.4f +
           GetSquaredWaveValue(frequency, currentCount) * 0.4 +
           GetSquaredWaveValue(frequency * 2.f, currentCount) * 0.15 +
           GetNoiseValue() * 0.05;
}

float CreateFluteSound(float frequency, long int currentCount)
{
    return (GetSineWaveValue(frequency, currentCount) * 0.4f +
            GetSineWaveValue(frequency * 2, currentCount) * 0.1f +
            GetSineWaveValue(frequency * 3, currentCount) * 0.15f +
            GetSineWaveValue(frequency * 4, currentCount) * 0.05f +
            GetSineWaveValue(frequency * 5, currentCount) * 0.2f +
            GetSineWaveValue(frequency * 6.3, currentCount) * 0.05f +
            GetSineWaveValue(frequency * 7.3, currentCount) * 0.05f +
            GetSineWaveValue(frequency * 8.3, currentCount) * 0.05f +
            GetSineWaveValue(frequency * 10, currentCount) * 0.05f) *
           (0.92 + 0.08 * GetSineWaveValue(10, currentCount));
}

float CreateSeaWavesSound(float frequency, long int currentCount)
{
    return GetLowPassNoiseValue(0.1f) *
               GetSineWaveValue(frequency, currentCount) * 0.9 +
           GetLowPassNoiseValue(0.1f) * 0.1;
}

float CreateDrumSound(float frequency, long int currentCount)
{
    return GetNoiseValue();
}

//=============================================================================
//      SOUND MANIPULATION
//=============================================================================

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
    static bool fire = false;
    static bool fire1 = false;
    static bool geometry = false;
    static float generalVolume = 0.2f;

    const Envelope fireEnv = {2.f, 0.f, 0.f, 1.f, 1.f, 0.5f};
    const Envelope seaEnv = {2.f, 0.f, 20.f, 7.f, 1.f, 1.f};
    const Envelope drumEnv = {0.f, 0.f, 0.f, 0.1f, 1.f, 1.f};
    const Envelope snareEnv = {0.05f, 0.f, 0.f, 0.05f, 1.f, 1.f};
    const Envelope fluteEnv = {0.125f, 0.f, 0.25f, 0.125f, 1.f, 1.f};
    const Envelope fluteEnv1 = {0.125f, 0.f, 0.75f, 0.125f, 1.f, 1.f};

    const Note fireNote = {CreateArmonicSound, fireEnv, 200.f, 0.6f * generalVolume};
    const Note seaNote = {CreateSeaWavesSound, seaEnv, 0.03f, 0.6f * generalVolume};
    const Note drumNote = {CreateDrumSound, drumEnv, 0.f, 0.6f * generalVolume};
    const Note snareNote = {CreateDrumSound, snareEnv, 0.f, 0.6f * generalVolume};
    const Note fluteNote = {CreateFluteSound, fluteEnv, 440.f, 0.6f * generalVolume};

    if (accumulatedTime > START_FIRE && !fire)
    {
        notes.push_back(fireNote);
        fire = true;
    }
    if (accumulatedTime > START_FIRE + 1.5f && !fire1)
    {
        Note aux = Note(fireNote);
        aux.frequency = 222;
        notes.push_back(aux);
        fire1 = true;
    }
    if (accumulatedTime > START_GEOMETRY + 2.f && !geometry)
    {
        notes.push_back(seaNote);
        geometry = true;
    }
    if (accumulatedTime > START_GEOMETRY + 16.f && accumulatedTime < START_GEOMETRY + 23.f)
    {
        notes[0].frequency += 0.08 * deltaTime;
    }
    if (accumulatedTime > START_GEOMETRY + 23.f && accumulatedTime < START_GEOMETRY + 23.1f)
    {
        notes[0].frequency = 0.6;
    }

    if (accumulatedTime > START_GEOMETRY + 30.f && accumulatedTime < START_GEOMETRY + 50.f)
    {
        static float accumulator = 0.f;
        accumulator += deltaTime;

        if (accumulator > 1.f)
        {
            notes.push_back(drumNote);
            accumulator = 0.f;
        }
    }
    if (accumulatedTime > START_GEOMETRY + 33.5f && accumulatedTime < START_GEOMETRY + 50.f)
    {
        static float accumulator = 0.f;
        accumulator += deltaTime;

        if (accumulator > 1.f)
        {
            notes.push_back(snareNote);
            accumulator = 0.f;
        }
    }
    if (accumulatedTime > START_GEOMETRY + 35.f && accumulatedTime < START_ENDING)
    {
        static float accumulator = 0.f;
        static float accumulator1 = 0.66f;
        static float lastFrequency = fluteNote.frequency;
        static float tone = 1.059463;
        accumulator += deltaTime;
        accumulator1 += deltaTime;

        if (accumulator > 0.33f)
        {
            Note aux = fluteNote;
            if (Fast::Rand() % 2 == 0)
            {
                aux.frequency = lastFrequency * pow(tone, Fast::Rand() % 3);
            }
            else
            {
                aux.frequency = lastFrequency / pow(tone, Fast::Rand() % 3);
            }

            lastFrequency = aux.frequency;
            notes.push_back(aux);
            accumulator = 0.f;
        }
        if (accumulator1 > 1.f)
        {
            Note aux = fluteNote;
            aux.frequency = lastFrequency * 0.5;
            aux.envelope = fluteEnv1;
            notes.push_back(aux);
            accumulator1 = 0.f;
        }
    }

    UpdateEnvelopes(deltaTime);
    RemoveDeadNotes();
}