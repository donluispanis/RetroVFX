#include "PlanesDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/PerlinNoise2D.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool PlanesDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
    texture = nullptr;

    float *noiseMap;
    int size;

    PerlinNoise2D p2D(8);
    p2D.Build(noiseMap, size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            pixels[j * width + i] = Pixel(255) * noiseMap[j * size + i];
        }
    }
    return true;
}

bool PlanesDemo::Destroy()
{
    return true;
}

bool PlanesDemo::Update(float deltaTime)
{
    

    RenderText("dfsgdftgh", 5, 5, 2, Pixel(255));
    return true;
}