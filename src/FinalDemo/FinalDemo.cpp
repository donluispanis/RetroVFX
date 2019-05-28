#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

#include "Imp/Imp_Audio.cpp"
#include "Imp/Imp_Fire.cpp"
#include "Imp/Imp_Geometry.cpp"
#include "Imp/Imp_Plasma.cpp"
#include "Imp/Imp_Planes.cpp"
#include "Imp/Imp_Ending.cpp"

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    InitFire();
    InitGeometry();
    InitPlasma();
    InitPlanes();
    InitEnding();

    accumulatedTime = 0;

    InitAudio();

    return true;
}

bool FinalDemo::Destroy()
{
    CloseFire();
    CloseGeometry();
    ClosePlasma();
    ClosePlanes();
    CloseEnding();

    CloseAudio();
    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    if (accumulatedTime > START_FIRE && accumulatedTime < DURATION_FIRE + START_FIRE)
    {
        UpdateFire(deltaTime);
    }
    if (accumulatedTime > START_GEOMETRY && accumulatedTime < DURATION_GEOMETRY + START_GEOMETRY)
    {
        UpdateGeometry(deltaTime);
    }
    if(accumulatedTime > START_PLASMA && accumulatedTime < DURATION_PLASMA + START_PLASMA)
    {
        UpdatePlasma(deltaTime);
    }
    if(accumulatedTime > START_PLANES && accumulatedTime < DURATION_PLANES + START_PLANES)
    {
        UpdatePlanes(deltaTime);
    }
    if(accumulatedTime > START_ENDING && accumulatedTime < DURATION_ENDING + START_ENDING)
    {
        UpdateEnding(deltaTime);
    }
    if(accumulatedTime > DURATION_TOTAL)
    {
        return false;
    }

    UpdateSound(deltaTime);

    return true;
}