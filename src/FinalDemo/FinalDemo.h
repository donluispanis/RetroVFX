#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"

#include "Imp/Imp_Fire.h"
#include "Imp/Imp_Geometry.h"
#include "Imp/Imp_Plasma.h"
#include "Imp/Imp_Planes.h"
#include "Imp/Imp_Ending.h"
#include "Imp/Imp_Audio.h"

struct Pixel;
struct IWindowManager;
struct TurbulencePath;

class FinalDemo : public ClassicDemoTemplate
{
public:
    FinalDemo(){};
    virtual ~FinalDemo(){};

    void DrawCharacterOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, char character, int scale);
    void DrawCharactersOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, const char *characters, int scale);

private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;
    float accumulatedTime;

    const int mathTableSize = 1024;
    float* cosineTable, *sineTable;

    bool tunnelBeat = false;

    //TIMING VARIABLES
    const float DURATION_FIRE = 5.0f;
    const float DURATION_GEOMETRY = 75.0f;
    const float DURATION_PLASMA = 30.0f;
    const float DURATION_PLANES = 42.0f;
    const float DURATION_ENDING = 40.0f;
    const float DURATION_TOTAL = DURATION_FIRE + DURATION_GEOMETRY + DURATION_PLASMA + DURATION_PLANES + DURATION_ENDING;

    const float START_FIRE = 600.f;
    const float START_GEOMETRY = START_FIRE + DURATION_FIRE;
    const float START_PLASMA = START_GEOMETRY + DURATION_GEOMETRY;
    const float START_PLANES = START_PLASMA + DURATION_PLASMA;
    const float START_ENDING = 0;//START_PLANES + DURATION_PLANES;

    //Implementations
    Imp_Fire fire;
    Imp_Geometry geometry;
    Imp_Plasma plasma;
    Imp_Planes planes;
    Imp_Ending ending;
    Imp_Audio audio;
};