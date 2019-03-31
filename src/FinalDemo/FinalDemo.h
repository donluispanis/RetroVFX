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
    float accumulatedTime;

    //Sound
    void InitAudio();
    void UpdateSound(float deltaTime);
    void CloseAudio();
    PaStream *stream;

    //Geometry
    void InitGeometry();
    void UpdateGeometry(float deltaTime);
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
    void UpdateFire();
    void CloseFire();
    void InitSmallFireText();
    void DrawSmallFireText();
    void DrawCharacterOnFireMap(unsigned char* map, int width, unsigned char value, int x, int y, char character, int scale);

    unsigned char *screenMapping;
    unsigned char *fireMapping;
    Pixel *colourMap;
    int colourMapSize = 256;
};

//SOUND
const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int INPUT_CHANNELS = 0;
const int OUTPUT_CHANNELS = 2;

const int NOTE_ARRAY_SIZE = 1;

float GetSquaredWaveValue(int frequency, long int currentCount);
float GetSawtoothWaveValue(int frequency, long int currentCount);
float GetTriangleWaveValue(int frequency, long int currentCount);
float GetSineWaveValue(int frequency, long int currentCount);
float GetNoiseValue();
float GetLowPassNoiseValue(float intensity);