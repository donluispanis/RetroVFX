#include "PlanesDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/PerlinNoise.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool PlanesDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    PerlinNoise p(8);


    float* noiseMap;
    int size;
    p.Build(noiseMap, size);

    for(int i = 0; i < size; i++)
    {
        int j = height - noiseMap[i];
        pixels[j * width + i] = Pixel(255);
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
