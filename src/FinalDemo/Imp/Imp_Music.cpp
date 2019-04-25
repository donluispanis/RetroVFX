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
    float (*generateWave)(int frequency, long int currentCount);
    Envelope envelope;
    int frequency = 440;
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
float CreateArmonicSound(int frequency, long int currentCount)
{
    return GetSawtoothWaveValue(frequency * 0.5, currentCount) * 0.4f +
           GetSquaredWaveValue(frequency, currentCount) * 0.4 +
           GetSquaredWaveValue(frequency * 2, currentCount) * 0.15 +
           GetNoiseValue() * 0.05;
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

    const Envelope env = {2.f, 0.f, 0.f, 1.f, 1.f, 0.5f};
    const Note note = {CreateArmonicSound, env, 200};

    if (accumulatedTime > START_FIRE && !fire)
    {
        notes.push_back(note);
        fire = true;
    }
    if (accumulatedTime > START_FIRE + 1.5f && !fire1)
    {
        Note aux = Note(note);
        aux.frequency = 222;
        notes.push_back(aux);
        fire1 = true;
    }

    UpdateEnvelopes(deltaTime);
    RemoveDeadNotes();
}