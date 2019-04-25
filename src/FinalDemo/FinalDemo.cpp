#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

#include "Imp/Imp_Audio.cpp"
#include "Imp/Imp_Fire.cpp"
#include "Imp/Imp_Geometry.cpp"

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    InitFire();
    InitGeometry();

    accumulatedTime = 0;

#ifdef _WIN32
    InitAudio();
#endif

    return true;
}

bool FinalDemo::Destroy()
{
    CloseFire();
    CloseGeometry();

#ifdef _WIN32
    CloseAudio();
#endif

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    if (accumulatedTime > START_FIRE && accumulatedTime < 5.0f + START_FIRE)
    {
        UpdateFire(deltaTime);
    }
    if (accumulatedTime > START_GEOMETRY && accumulatedTime < 5.0f + START_GEOMETRY)
    {
        UpdateGeometry(deltaTime);
    }

#ifdef _WIN32
    UpdateSound(deltaTime);
#endif

    return true;
}