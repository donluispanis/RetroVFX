#include "Imp_Audio.h"
#include "Sounds.h"
#include "../../Utils/Fast.h"
#include <cmath>

std::vector<Imp_Audio::Note> Imp_Audio::notes;

void Imp_Audio::InitAudio(int startFire, int startGeometry, int startPlasma, int startPlanes, int startEnding)
{
    START_FIRE = startFire;
    START_GEOMETRY = startGeometry;
    START_PLASMA = startPlasma;
    START_PLANES = startPlanes;
    START_ENDING = startEnding;

    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, AudioCallback, 0);
    Pa_StartStream(stream);

    InitNotes();
}

void Imp_Audio::CloseAudio()
{
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}

void Imp_Audio::UpdateSound(float deltaTime, float accumulatedTime, bool tunnelBeat)
{
    UpdateFireSound(accumulatedTime);
    UpdateWavesSound(accumulatedTime, deltaTime);
    UpdateTransitioningSphereSound(accumulatedTime);
    UpdateIncresingSpherePhaseSound(accumulatedTime, deltaTime);
    UpdateScaleChangingSphereSound(accumulatedTime, deltaTime);
    UpdatePlasmaIntroSound(accumulatedTime);
    UpdatePlasmaDrums(accumulatedTime, deltaTime);
    UpdatePlasmaMelody(accumulatedTime, deltaTime);
    UpdatePlasmaRotozoomSound(accumulatedTime, deltaTime);
    UpdatePlanesSound(accumulatedTime, deltaTime);
    UpdateEndingSound(accumulatedTime, deltaTime, tunnelBeat);

    UpdateEnvelopes(deltaTime);
    RemoveDeadNotes();
}

int Imp_Audio::AudioCallback(const void *inputBuffer, void *outputBuffer,
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

        Imp_Audio::UpdateNotes(currentCount);

        *out++ = Imp_Audio::GetLeftValue();  /* left */
        *out++ = Imp_Audio::GetRightValue(); /* rigth */
    }
    return 0;
}

void Imp_Audio::UpdateNotes(long int currentCount)
{
    for (auto &note : notes)
    {
        note.resultingSound = note.generateWave(note.frequency, currentCount) * note.currentEnvelopeValue * note.volume;
    }
}

float Imp_Audio::GetLeftValue()
{
    float sum = 0.f;

    for (auto &note : notes)
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

float Imp_Audio::GetRightValue()
{
    float sum = 0.f;

    for (auto &note : notes)
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

void Imp_Audio::UpdateFireSound(float accumulatedTime)
{
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
}

void Imp_Audio::UpdateWavesSound(float accumulatedTime, float deltaTime)
{
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
}

void Imp_Audio::UpdateTransitioningSphereSound(float accumulatedTime)
{
    if (accumulatedTime > START_GEOMETRY + 30.f)
    {
        if (!geometry1)
        {
            Note auxNote = synthNote;
            auxNote.envelope.sustain = 6.f;
            auxNote.frequency = 220.f;
            notes.push_back(auxNote);
            geometry1 = true;
        }

        static Note &note = notes[notes.size() - 1];
        note.frequency = note.frequency + cos(accumulatedTime) * 0.5f;
        note.position = 0.5f + cos(accumulatedTime) * 0.5f;
    }
}

void Imp_Audio::UpdateIncresingSpherePhaseSound(float accumulatedTime, float deltaTime)
{
    if (accumulatedTime > START_GEOMETRY + 39.f && accumulatedTime < START_GEOMETRY + 55.f)
    {
        static float accumulator = 0.7f;
        static float maxAccumulator = 0.6f;
        static float volume = 1.f;

        accumulator += deltaTime;
        maxAccumulator = 0.5 - 0.3 * ((accumulatedTime - START_GEOMETRY - 40.f) / 13.f);

        if (maxAccumulator <= 0.f)
        {
            maxAccumulator = 0.001f;
        }

        if (accumulator >= maxAccumulator)
        {
            accumulator = 0.f;

            static float baseFrequency = 523.f * 0.125;
            const static float incrementer = 1.059463f;
            Envelope auxEnv = laserEnv;
            auxEnv.release = maxAccumulator;

            //Generate Sephard illusion of descending sound
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 1, mask[1] * volume, 0.3f});
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 2, mask[3] * volume, 0.7f});
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 4, mask[5] * volume, 0.3f});
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 6, mask[7] * volume, 0.7f});
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 8, mask[9] * volume, 0.3f});
            notes.push_back({Sounds::CreateLaserSound, auxEnv, baseFrequency * 10, mask[11] * volume, 0.7f});

            baseFrequency /= incrementer;
            if (baseFrequency <= 261.f * 0.125)
            {
                baseFrequency = 523.f * 0.125;
            }
        }
    }
}

void Imp_Audio::UpdateScaleChangingSphereSound(float accumulatedTime, float deltaTime)
{
    static std::deque<float> geometryFrequencies = {DO, RE, MI, RE};
    if (accumulatedTime > START_GEOMETRY + 55.f && accumulatedTime < START_PLASMA && geometryFrequencies.size() > 0)
    {
        static float accumulator = 4.5f;
        accumulator += deltaTime;
        if (accumulator > 4.f)
        {
            Note aux = synthNote;
            aux.frequency = geometryFrequencies.front();

            if (geometryFrequencies.size() == 1)
            {
                aux.envelope.sustain = 2.f;
                aux.envelope.release = 3.f;
            }

            notes.push_back(aux);

            geometryFrequencies.pop_front();
            accumulator = 0.f;
        }
    }
}

void Imp_Audio::UpdatePlasmaIntroSound(float accumulatedTime)
{
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
}

void Imp_Audio::UpdatePlasmaDrums(float accumulatedTime, float deltaTime)
{
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
            if (volume < 0.f)
            {
                volume = 0.f;
            }
        }

        if (accumulator0 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            aux.position = 0.3f;
            notes.push_back(aux);
            accumulator0 = 0.f;
        }
        if (accumulator1 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            aux.position = 0.3f;
            notes.push_back(aux);
            accumulator1 = 0.f;
        }
        if (accumulator2 > 1.f)
        {
            Note aux = snareNote;
            aux.volume = volume;
            aux.position = 0.7f;
            notes.push_back(aux);
            accumulator2 = 0.f;
        }
    }
}

void Imp_Audio::UpdatePlasmaMelody(float accumulatedTime, float deltaTime)
{
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
                aux.position = 0.5f - counter * 0.04f;
                aux.volume = counter * 0.05;
            }
            else
            {
                aux.volume = 0.5f;
            }
            if (aux.volume < 0.f)
            {
                aux.volume = 0.f;
            }

            notes.push_back(aux);

            plasmaFrequencies.pop_front();
            accumulator = 0.f;
        }
    }
}

void Imp_Audio::UpdatePlasmaRotozoomSound(float accumulatedTime, float deltaTime)
{
    if (accumulatedTime > START_PLASMA + 13.f && accumulatedTime < START_PLASMA + 30.f)
    {
        static float accumulator = 0.7f;
        static float maxAccumulator = 0.6f;
        static float volume = 1.f;

        accumulator += deltaTime;
        maxAccumulator = 0.8 - 0.8 * ((accumulatedTime - START_PLASMA - 13.f) / 15.f);

        if (maxAccumulator <= 0.f)
        {
            maxAccumulator = 0.001f;
        }

        //fade out
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

            //Generate Sephard illusion of ascending sound
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 1, mask[1] * volume, 0.3f});
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 2, mask[3] * volume, 0.7f});
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 4, mask[5] * volume, 0.3f});
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 6, mask[7] * volume, 0.7f});
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 8, mask[9] * volume, 0.3f});
            notes.push_back({Sounds::GetSineWaveValue, laserEnv, baseFrequency * 10, mask[11] * volume, 0.7f});

            baseFrequency *= incrementer;
            if (baseFrequency >= 523.f)
            {
                baseFrequency = 261.63f;
            }
        }
    }
}

void Imp_Audio::UpdatePlanesSound(float accumulatedTime, float deltaTime)
{
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
                aux.position = 0.3f;
                notes.push_back(aux);
            }

            if (planesFrequencies.size() < 13)
            {
                planesFrequencies.pop_front();
                aux.volume = 0.4f;
                aux.frequency = planesFrequencies.front();
                aux.position = 0.7f;
                notes.push_back(aux);
            }

            planesFrequencies.pop_front();
            accumulator = 0.f;
        }
    }
}

void Imp_Audio::UpdateEndingSound(float accumulatedTime, float deltaTime, bool tunnelBeat)
{
    if (accumulatedTime > START_ENDING + 8.f)
    {
        static float accumulator = 1.f;
        static float accumulator1 = 0.95f;
        static float accumulator2 = 0.f;
        static float volume = 0.4f;
        static bool lastBeat = false;
        accumulator += deltaTime;
        accumulator1 += deltaTime;
        accumulator2 += deltaTime * Fast::PI * 0.5f;

        //Fade out
        if (accumulatedTime > START_ENDING + 35.f)
        {
            volume -= deltaTime * 0.25f;
            if (volume < 0.f)
            {
                volume = 0.f;
            }
        }

        //Melody
        if (accumulator > 0.25f)
        {
            static float position = 0.5f;
            position = 0.5f + cos(accumulator2) * 0.5f;

            Note aux = laserNote;
            aux.volume = volume;
            aux.frequency = frequencies.front();
            aux.position = position;
            notes.push_back(aux);
            frequencies.pop_front();
            accumulator = 0.f;
        }
        //Drums
        if (tunnelBeat && accumulator1 > 1.f)
        {
            Note aux = drumNote;
            aux.volume = volume;
            if (lastBeat)
            {
                aux.position = 0.2f;
                lastBeat = false;
            }
            else
            {
                aux.position = 0.8f;
                lastBeat = true;
            }

            notes.push_back(aux);
            accumulator1 = 0.f;
        }
    }
}

void Imp_Audio::InitNotes()
{
    fireEnv = {2.f, 0.f, 0.f, 1.f, 1.f, 0.5f};
    seaEnv = {2.f, 0.f, 20.f, 7.f, 1.f, 1.f};
    drumEnv = {0.f, 0.f, 0.f, 0.1f, 1.f, 1.f};
    snareEnv = {0.f, 0.f, 0.f, 0.3f, 1.f, 0.5f};
    synthEnv = {1.f, 1.f, 1.f, 2.f, 1.f, 0.7f};
    laserEnv = {0.0f, 0.f, 0.0f, 0.2f, 1.f, 1.0f};

    fireNote = {Sounds::CreateRetroSound, fireEnv, 200.f, 0.6f * generalVolume};
    seaNote = {Sounds::CreateSeaWavesSound, seaEnv, 0.07f, 0.6f * generalVolume};
    drumNote = {Sounds::CreateDrumSound, drumEnv, 0.f, 0.6f * generalVolume};
    snareNote = {Sounds::CreateDrumSound, snareEnv, 0.f, 0.6f * generalVolume};
    synthNote = {Sounds::CreateSynthSound, synthEnv, 440.f, 1.f * generalVolume};
    laserNote = {Sounds::CreateLaserSound, laserEnv, 440.f, 0.6f * generalVolume};

    frequencies = {DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA,
                   DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA,
                   DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA,
                   DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA,
                   DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA,
                   DO, SI, DO, SI, RE, LA, RE, LA, DO, LA, DO, LA, RE, SI, RE, SI,
                   RE, LA, RE, LA, MI, SOL, MI, SOL, RE, SOL, RE, SOL, MI, LA, MI, LA};
    planesFrequencies = {DO, SOL, LA, FA,
                         DO, MI, SOL, SI, LA, DO * 2, FA, LA,
                         DO, MI, SOL, SOL, SI, RE * 2, LA, DO * 2, MI * 2, FA, LA, DO * 2};
    plasmaFrequencies = {DO, SI, DO, SI, DO, LA, DO, LA, RE, SI,
                         RE, SI, RE, LA, RE, LA, MI, LA, MI, LA,
                         FA, LA, FA, LA, FA, SOL, FA, SOL, LA, LA,
                         SOL, FA, MI, RE, DO, SI * 0.5, LA * 0.5, SOL * 0.5, FA * 0.5, MI * 0.5};
}

void Imp_Audio::UpdateEnvelopes(float deltaTime)
{
    for (auto &note : notes)
    {
        Envelope env = note.envelope;
        note.lifetime += deltaTime;

        float life = note.lifetime;

        if (life < env.attack)
        {
            note.currentEnvelopeValue = env.peakAmplitude * (life / env.attack);

            if (env.attack == 0.f)
            {
                note.currentEnvelopeValue = 0.f;
            }
        }
        else if (life < env.attack + env.decay)
        {
            float t = (life - env.attack) / env.decay;

            if (env.decay == 0.f)
            {
                t = 0.f;
            }

            note.currentEnvelopeValue = t * env.peakAmplitude + (1 - t) * env.sustainAmplitude;
        }
        else if (life < env.attack + env.decay + env.sustain)
        {
            note.currentEnvelopeValue = env.sustainAmplitude;
        }
        else if (life < env.attack + env.decay + env.sustain + env.release)
        {
            note.currentEnvelopeValue = (((env.attack + env.decay + env.sustain + env.release) - life) / env.release) * env.sustainAmplitude;

            if (env.release == 0.f)
            {
                note.currentEnvelopeValue = 0.f;
            }
        }
        else
        {
            note.currentEnvelopeValue = -1.f;
        }
    }
}

void Imp_Audio::RemoveDeadNotes()
{
    for (unsigned int i = 0; i < notes.size(); i++)
    {
        if (notes[i].currentEnvelopeValue < 0.f)
        {
            notes.erase(notes.begin() + i);
            i--;
        }
    }
}