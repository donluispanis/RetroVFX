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
    UpdateFire();
    UpdateGeometry(deltaTime);
    return true;
}