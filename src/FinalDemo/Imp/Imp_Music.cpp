#include "Imp_Includes.h"
#include <deque>

#define DO 261.626f
#define RE 293.665f
#define MI 329.628f
#define FA 349.228f
#define SOL 391.995f
#define LA 440.f
#define SI 493.883f

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

float CreateSynthSound(float frequency, long int currentCount)
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

static float mask[12] = {0.01f, 0.025f, 0.05f, 0.075f, 0.14f, 0.2f, 0.2f, 0.14f, 0.075f, 0.05f, 0.025f, 0.01f};

void RotateMask()
{
    const float lastNote = mask[11];
    for (int i = 10; i == 0; i--)
    {
        float a = mask[i + 1];
        float b = mask[i];
        mask[i + 1] = mask[i];
    }
    mask[0] = lastNote;
}

float CreateLaserSound(float frequency, long int currentCount)
{
    return (GetSawtoothWaveValue(frequency, currentCount) * 0.5f +
            GetSawtoothWaveValue(frequency, currentCount) * 0.5f * GetHighPassNoiseValue(0.05)) *
               0.5 +
           GetHighPassNoiseValue(0.05) * 0.5;
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
    static bool geometry1 = false;
    static bool geometry2 = false;
    static bool plasma = false;
    static float generalVolume = 1.f;

    const Envelope fireEnv = {2.f, 0.f, 0.f, 1.f, 1.f, 0.5f};
    const Envelope seaEnv = {2.f, 0.f, 20.f, 7.f, 1.f, 1.f};
    const Envelope drumEnv = {0.f, 0.f, 0.f, 0.1f, 1.f, 1.f};
    const Envelope snareEnv = {0.f, 0.f, 0.f, 0.3f, 1.f, 0.5f};
    const Envelope fluteEnv = {0.125f, 0.f, 0.25f, 0.125f, 1.f, 1.f};
    const Envelope fluteEnv1 = {0.125f, 0.f, 0.75f, 0.125f, 1.f, 1.f};
    const Envelope synthEnv = {1.f, 1.f, 1.f, 2.f, 1.f, 0.7f};
    const Envelope laserEnv = {0.0f, 0.f, 0.0f, 0.2f, 1.f, 1.0f};

    const Note fireNote = {CreateArmonicSound, fireEnv, 200.f, 0.6f * generalVolume};
    const Note seaNote = {CreateSeaWavesSound, seaEnv, 0.07f, 0.6f * generalVolume};
    const Note drumNote = {CreateDrumSound, drumEnv, 0.f, 0.6f * generalVolume};
    const Note snareNote = {CreateDrumSound, snareEnv, 0.f, 0.6f * generalVolume};
    const Note fluteNote = {CreateFluteSound, fluteEnv, 440.f, 0.6f * generalVolume};
    const Note synthNote = {CreateSynthSound, synthEnv, 440.f, 1.f * generalVolume};
    const Note laserNote = {CreateLaserSound, laserEnv, 440.f, 0.6f * generalVolume};

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
    if (accumulatedTime > START_GEOMETRY + 30.f)
    {
        if (!geometry1)
        {
            Note auxNote = synthNote;
            auxNote.envelope.sustain = 6.f;
            notes.push_back(auxNote);
            geometry1 = true;
        }

        static Note &note = notes[notes.size() - 1];
        note.frequency = note.frequency + cos(accumulatedTime);
    }
    if (accumulatedTime > START_GEOMETRY + 39.f && accumulatedTime < START_GEOMETRY + 55.f)
    {
        static float accumulator = 0.7f;
        static float maxAccumulator = 0.6f;
        static float volume = 1.f;

        accumulator += deltaTime;
        maxAccumulator = 0.5 - 0.3 * ((accumulatedTime - START_GEOMETRY - 40.f) / 13.f);
        if (accumulator >= maxAccumulator)
        {
            accumulator = 0.f;

            static float baseFrequency = 523.f * 0.125;
            const static float incrementer = 1.059463f;
            Envelope auxEnv = laserEnv;
            auxEnv.release = maxAccumulator;

            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 1, mask[1] * volume});
            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 2, mask[3] * volume});
            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 4, mask[5] * volume});
            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 6, mask[7] * volume});
            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 8, mask[9] * volume});
            notes.push_back({CreateLaserSound, auxEnv, baseFrequency * 10, mask[11] * volume});

            baseFrequency /= incrementer;
            if (baseFrequency <= 261.f * 0.125)
            {
                baseFrequency = 523.f * 0.125;
            }
        }
    }
    if (accumulatedTime > START_GEOMETRY + 55.f && accumulatedTime < START_PLASMA)
    {
        static float accumulator = 4.5f;
        accumulator += deltaTime;
        static std::deque<float> frequencies = {DO, RE, MI, RE};
        if (accumulator > 4.f)
        {
            Note aux = synthNote;
            aux.frequency = frequencies.front();

            if (frequencies.size() == 1)
            {
                aux.envelope.sustain = 2.f;
                aux.envelope.release = 3.f;
            }

            notes.push_back(aux);

            frequencies.pop_front();
            accumulator = 0.f;
        }
    }
    if (accumulatedTime > START_PLASMA && !plasma)
    {
        Note auxNote = fireNote;
        auxNote.frequency = 200.f;
        auxNote.envelope.attack = 4.f;
        auxNote.envelope.release = 2.f;
        auxNote.envelope.sustainAmplitude = 1.f;
        notes.push_back(auxNote);
        plasma = true;
    }
    if (accumulatedTime > START_PLASMA && accumulatedTime < START_PLASMA + 13.f)
    {
        static float accumulator0 = 0.9f;
        static float accumulator1 = 0.6f;
        static float accumulator2 = 0.3f;
        static float volume = 0.25f;
        accumulator0 += deltaTime;
        accumulator1 += deltaTime;
        accumulator2 += deltaTime;

        if (accumulatedTime > START_PLASMA + 8.f)
        {
            volume -= deltaTime * 0.04;
        }

        if (accumulator0 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            notes.push_back(aux);
            accumulator0 = 0.f;
        }
        if (accumulator1 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            notes.push_back(aux);
            accumulator1 = 0.f;
        }
        if (accumulator2 > 1.f)
        {
            Note aux = snareNote;
            aux.volume = volume;
            notes.push_back(aux);
            accumulator2 = 0.f;
        }
    }
    static std::deque<float> plasmaFrequencies = {DO, SI, DO, SI, DO, LA, DO, LA, RE, SI,
                                                  RE, SI, RE, LA, RE, LA, MI, LA, MI, LA,
                                                  FA, LA, FA, LA, FA, SOL, FA, SOL, LA, LA,
                                                  SOL, FA, MI, RE, DO, SI * 0.5, LA * 0.5, SOL * 0.5, FA * 0.5, MI * 0.5};
    if (accumulatedTime > START_PLASMA + 5.1f && plasmaFrequencies.size() > 0)
    {
        static float accumulator = 1.f;
        static int counter = 11;
        accumulator += deltaTime;

        if (accumulator > 0.33)
        {
            Note aux = laserNote;
            aux.frequency = plasmaFrequencies.front();
            if (plasmaFrequencies.size() < 11)
            {
                counter--;
                aux.volume = counter * 0.05;
            }
            else
            {
                aux.volume = 0.5f;
            }
            notes.push_back(aux);

            plasmaFrequencies.pop_front();
            accumulator = 0.f;
        }
    }
    if (accumulatedTime > START_PLASMA + 13.f && accumulatedTime < START_PLASMA + 30.f)
    {
        static float accumulator = 0.7f;
        static float maxAccumulator = 0.6f;
        static float volume = 1.f;

        accumulator += deltaTime;
        maxAccumulator = 0.8 - 0.8 * ((accumulatedTime - START_PLASMA - 13.f) / 15.f);

        if (accumulatedTime > START_PLASMA + 28.f)
        {
            volume -= deltaTime * 0.75f;

            if (volume < 0.f)
            {
                volume = 0.f;
            }
        }

        if (accumulator >= maxAccumulator)
        {
            accumulator = 0.f;

            static float baseFrequency = 261.63 * 0.125;
            const static float incrementer = 1.059463f;

            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 1, mask[1] * volume});
            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 2, mask[3] * volume});
            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 4, mask[5] * volume});
            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 6, mask[7] * volume});
            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 8, mask[9] * volume});
            notes.push_back({GetSineWaveValue, laserEnv, baseFrequency * 10, mask[11] * volume});

            baseFrequency *= incrementer;
            if (baseFrequency >= 523.f)
            {
                baseFrequency = 261.63f;
            }
        }
    }
    static std::deque<float> planesFrequencies = {DO, SOL, LA, FA,
                                                  DO, MI, SOL, SI, LA, DO * 2, FA, LA,
                                                  DO, MI, SOL, SOL, SI, RE * 2, LA, DO * 2, MI * 2, FA, LA, DO * 2};
    if (accumulatedTime > START_PLANES && planesFrequencies.size() > 0)
    {
        static float accumulator = 4.f;
        accumulator += deltaTime;

        if (accumulator >= 3.5f)
        {
            Note aux = synthNote;
            aux.frequency = planesFrequencies.front();
            aux.volume = 0.2f;
            notes.push_back(aux);

            if (planesFrequencies.size() < 21)
            {
                planesFrequencies.pop_front();
                aux.volume = 0.3f;
                aux.frequency = planesFrequencies.front();
                notes.push_back(aux);
            }

            if (planesFrequencies.size() < 13)
            {
                planesFrequencies.pop_front();
                aux.volume = 0.4f;
                aux.frequency = planesFrequencies.front();
                notes.push_back(aux);
            }

            planesFrequencies.pop_front();
            accumulator = 0.f;
        }
    }
    if (accumulatedTime > START_ENDING + 8.f)
    {
        static std::deque<float> frequencies = {DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA,
                                                DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA,
                                                DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA,
                                                DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA,
                                                DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA,
                                                DO, SI, DO, SI, RE, LA, RE, LA,
                                                DO, LA, DO, LA, RE, SI, RE, SI,
                                                RE, LA, RE, LA, MI, SOL, MI, SOL,
                                                RE, SOL, RE, SOL, MI, LA, MI, LA};
        static float accumulator = 1.f;
        static float accumulator1 = 0.95f;
        static float volume = 0.4f;
        accumulator += deltaTime;
        accumulator1 += deltaTime;


        if (accumulatedTime > START_ENDING + 30.f)
        {
            volume -= deltaTime * 0.11f;
            if (volume < 0.f)
            {
                volume = 0.f;
            }
        }

        if (accumulator > 0.25f)
        {
            Note aux = laserNote;
            aux.volume = volume;
            aux.frequency = frequencies.front();
            notes.push_back(aux);
            frequencies.pop_front();
            accumulator = 0.f;
        }
        if (tunnelBeat && accumulator1 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            notes.push_back(aux);
            accumulator1 = 0.f;
        }
    }

    UpdateEnvelopes(deltaTime);
    RemoveDeadNotes();
}