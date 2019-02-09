#include "PlasmaDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/InputValues.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool PlasmaDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    return true;
}

bool PlasmaDemo::Update(float deltaTime)
{
    RenderText("Plasma", 5, 5, 2, Pixel(255));
    return true;
}

bool PlasmaDemo::Destroy()
{
    return true;
}