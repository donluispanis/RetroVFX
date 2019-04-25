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

#ifdef _WIN32
    InitAudio();
    #endif
    InitFire();
    InitGeometry();

    accumulatedTime = 0;

    return true;
}

bool FinalDemo::Destroy()
{
    #ifdef _WIN32
    CloseAudio();
    #endif
    CloseFire();
    CloseGeometry();

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    if(accumulatedTime < 5.0f)
    {
        UpdateFire(deltaTime);
    }

#ifdef _WIN32
    UpdateSound(deltaTime);
#endif

    //UpdateGeometry(deltaTime);
    return true;
}