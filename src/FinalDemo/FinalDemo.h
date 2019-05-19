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
    void GenerateSphere(int gridSize, float radius);
    void GeneratePerspectiveProjection(Object3D &object);
    void RenderObject(Object3D object);
    void EraseObject(Object3D object);
    void TranslateObject(Object3D &object, Point3D offset);
    void ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime);
    void ApplyObjectTransformations(float deltaTime);
    void UndoObjectTransformations(float deltaTime);
    Point3D GetPointInSphereFromPlane(const int gridX, const int gridY, const int gridSize, const float radius);

    Object3D grid;
    Object3D sphere;
    const int vertexPerWidth = 30;
    const int vertexPerDepth = 30;
    const int vertexDistance = 250;
    float phase = 0.f;
    float phaseVelocity = 1.f;

    float waveAmplitude = 0.f;
    float waveAmplitudeVelocity = 0.f;
    float colourOpacityIn = 0.f;
    float colourOpacityOut = 1.f;
    Point3D position;

    bool renderLines = true;

    Point3D colourDeformator = Point3D(1.f, 1.f, 1.f);

    //Fire
    void InitFire();
    void UpdateFire(float deltaTime);
    void CloseFire();
    void InitBigFireText(int size, int value);
    void InitSmallFireText(int size, int value);
    void DrawBigFireText();
    void DrawSmallFireText();
    void DrawCharacterOnFireMap(unsigned char *map, int width, unsigned char value, int x, int y, char character, int scale);

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

    //Plasma
    void InitPlasma();
    void UpdatePlasma(float deltaTime);
    void ClosePlasma();

    const int mathTableSize = 1024;
    float *sineTable;

    const int plasmaColourMapSize = 256;
    Pixel *plasmaColourMap;
    Pixel *lavaColourMap;

    //Planes
    void InitPlanes();
    void UpdatePlanes(float deltaTime);
    void ClosePlanes();

    Pixel *texture;
    int texWidth, texHeight;

    void DrawCharacterOnPlanesMap(Pixel *map, int width, const Pixel &colour, int x, int y, char character, int scale);
    void DrawCharactersOnPlanesMap(Pixel *map, int width, const Pixel &colour, int x, int y, const char *characters, int scale);

    //TIMING VARIABLES
    const float DURATION_FIRE = 5.0f;
    const float DURATION_GEOMETRY = 75.0f;
    const float DURATION_PLASMA = 20.0f;
    const float DURATION_PLANES = 20.0f;

    const float START_FIRE = 20.f;
    const float START_GEOMETRY = START_FIRE + DURATION_FIRE;
    const float START_PLASMA = 0;
    const float START_PLANES = 0;
};

//SOUND
const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int INPUT_CHANNELS = 0;
const int OUTPUT_CHANNELS = 2;

float GetSquaredWaveValue(float frequency, long int currentCount);
float GetSawtoothWaveValue(float frequency, long int currentCount);
float GetTriangleWaveValue(float frequency, long int currentCount);
float GetSineWaveValue(float frequency, long int currentCount);
float GetNoiseValue();
float GetLowPassNoiseValue(float intensity);