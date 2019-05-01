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
    Point3D GetPointInSphereFromPlane(const int gridX, const int gridY, const int gridSize, const float radius);

    Object3D grid;
    const int vertexPerWidth = 6;
    const int vertexPerDepth = 6;
    const int vertexDistance = 250;
    float phase = 0;

    //Fire
    void InitFire();
    void UpdateFire(float deltaTime);
    void CloseFire();
    void InitBigFireText(int size, int value);
    void InitSmallFireText(int size, int value);
    void DrawBigFireText();
    void DrawSmallFireText();
    void DrawCharacterOnFireMap(unsigned char* map, int width, unsigned char value, int x, int y, char character, int scale);

    unsigned char *screenMapping;
    unsigned char *fireMapping;
    Pixel *colourMap;
    int colourMapSize = 256;

    int bigFireScale;
    int bigFireHeight;
    int bigFireCharCount;
    int bigFireCharSize;
    int bigFireTextStart;

    int smallFireScale;
    int smallFireHeight;
    int smallFireCharCount;
    int smallFireCharSize;
    int smallFireTextStart;

    //TIMING VARIABLES
    const float DURATION_FIRE = 5.0f;
    const float DURATION_GEOMETRY = 60.0f;
    const float START_FIRE = 60.f;
    const float START_GEOMETRY = 0.f;
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