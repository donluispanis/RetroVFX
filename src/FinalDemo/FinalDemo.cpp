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

    InitAudio();
    InitFire();
    InitGeometry();

    accumulatedTime = 0;

    return true;
}

bool FinalDemo::Destroy()
{
    CloseAudio();
    CloseFire();
    CloseGeometry();

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    accumulatedTime += deltaTime;

    UpdateSound(deltaTime);
    UpdateFire();
    //UpdateGeometry(deltaTime);
    return true;
}