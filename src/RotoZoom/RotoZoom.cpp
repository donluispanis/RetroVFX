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
    
    BMP::OpenRGBImage("assets/img/lena.bmp", texture, texWidth, texHeight);

    return true;
}

bool RotoZoom::Update(float deltaTime)
{
    for (int i = 0; i < texWidth; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            pixels[j * width + i] = texture[j * texWidth + i];
        }
    }
    
    RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

bool RotoZoom::Destroy()
{
    BMP::CloseRGBImage(texture);

    return true;
}