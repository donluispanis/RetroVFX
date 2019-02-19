#include "Geometry.h"
#include "../Utils/Pixel.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool GeometryDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    return true;
}

bool GeometryDemo::Update(float deltaTime)
{
    RenderText("Geometry", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

bool GeometryDemo::Destroy()
{
    return true;
}