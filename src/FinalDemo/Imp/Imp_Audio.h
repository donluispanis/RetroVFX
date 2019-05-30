#pragma once

#include <portaudio/portaudio.h>

class Imp_Audio
{
public:
    void InitAudio();
    void UpdateSound(float deltaTime);
    void CloseAudio();

    static float GetLeftValue();
    static float GetRightValue();

private:
    PaStream *stream;
};