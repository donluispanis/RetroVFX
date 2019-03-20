#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    return true;
}

bool FinalDemo::Destroy()
{
    return true;
}