#include "RotoZoom.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool RotoZoom::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    Pixel *image = nullptr;
    int widthd, heightd;
    BMP::LoadRGBImage("assets/img/lena.bmp", image, widthd, heightd);

    for (int i = 0; i < widthd; i++)
    {
        for (int j = 0; j < heightd; j++)
        {
            pixels[j * height + i] = image[j * heightd + i];
        }
    }

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