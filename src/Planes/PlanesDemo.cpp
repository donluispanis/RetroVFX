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
    texture = nullptr;

    Generate2DPerlinNoiseTexture();

    return true;
}

bool PlanesDemo::Destroy()
{
    return true;
}

bool PlanesDemo::Update(float deltaTime)
{
    for(int i = 0; i < texWidth; i++)
    {
        for(int j = 0; j < texHeight; j++)
        {
            pixels[j * width + i] = texture[j * texWidth + i];
        }
    }

    RenderText("dfsgdftgh", 5, 5, 2, Pixel(255));
    return true;
}

void PlanesDemo::Generate2DPerlinNoiseTexture()
{
    if (texture != nullptr)
    {
        delete[] texture;
    }

    float *noiseX, *noiseY;
    PerlinNoise pX(8), pY(8);

    pX.Build(noiseX, texWidth);
    pY.Build(noiseY, texHeight);

    texture = new Pixel[texWidth * texHeight];

    for(int i = 0; i < texWidth; i++)
    {
        for(int j = 0; j < texHeight; j++)
        {
            float path = j / float(texHeight);
            float value = noiseX[i] * path + noiseY[i] * (1 - path);
            Pixel p = Pixel(255) * value;
            texture[j * texWidth + i] = p;
        }
    }
}