#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Object3D.h"
#include "../Utils/ColourStamp.h"
#include <portaudio/portaudio.h>

struct Pixel;
struct IWindowManager;

class FinalDemo : public ClassicDemoTemplate
{
  public:
    FinalDemo(){};
    virtual ~FinalDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    //Sound
    void InitAudio();
    void CloseAudio();
    PaStream *stream;

    //Geometry
    void InitGeometry();
    void CloseGeometry();
    void GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance);
    void GeneratePerspectiveProjection(Object3D &object);
    void RenderObject(Object3D object);
    void EraseObject(Object3D object);
    void TranslateObject(Object3D &object, Point3D offset);
    void ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime);
    void ApplyObjectTransformations(float deltaTime);
    void UndoObjectTransformations(float deltaTime);

    Object3D grid;
    const int vertexPerWidth = 40;
    const int vertexPerDepth = 30;
    const int vertexDistance = 250;
    float phase = 0;

    //Fire
    void InitFire();
    void CloseFire();

    unsigned char *screenMapping;
    Pixel *colourMap;
    int colourMapSize = 256;
    std::vector<ColourStamp> colours;
};

//SOUND
const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int INPUT_CHANNELS = 0;
const int OUTPUT_CHANNELS = 2;

float GetSquaredWaveValue(int frequency, long int currentCount);
float GetSawtoothWaveValue(int frequency, long int currentCount);
float GetTriangleWaveValue(int frequency, long int currentCount);
float GetSineWaveValue(int frequency, long int currentCount);
float GetNoiseValue();
float GetLowPassNoiseValue(float intensity);
static int audioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);