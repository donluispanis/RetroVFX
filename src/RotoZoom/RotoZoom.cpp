#include "RotoZoom.h"
#include "../Utils/Pixel.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool RotoZoom::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    return true;
}

bool RotoZoom::Update(float deltaTime)
{
    RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}


bool RotoZoom::Destroy()
{
    return true;
}