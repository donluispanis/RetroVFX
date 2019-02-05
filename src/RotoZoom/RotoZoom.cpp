#include "RotoZoom.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
#include "../Utils/TurbulencePath.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool RotoZoom::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    mathTableSize = 1024;
    sineTable = new float[mathTableSize];
    Fast::GenerateSineTable(sineTable, mathTableSize);
    cosineTable = new float[mathTableSize];
    Fast::GenerateCosineTable(cosineTable, mathTableSize);

    offsetPath = new TurbulencePath(sineTable, cosineTable, mathTableSize);
    scaleAndAnglePath = new TurbulencePath(sineTable, cosineTable, mathTableSize);

    offsetPath->CreateTurbulencePath(3, height, 2);
    offsetPath->UpdateTurbulencePath(100, offsetX, offsetY);

    scaleAndAnglePath->CreateTurbulencePath(3, height, 2);
    scaleAndAnglePath->UpdateTurbulencePath(100, scale, angle);

    BMP::OpenRGBImage("assets/img/lena.bmp", texture, texWidth, texHeight);

    return true;
}

bool RotoZoom::Update(float deltaTime)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            DrawPixel(i, j, offsetX, offsetY, angle, scale);
        }
    }

    offsetPath->UpdateTurbulencePath(deltaTime, offsetX, offsetY);
    scaleAndAnglePath->UpdateTurbulencePath(deltaTime, scale, angle);
    scale /= (height / 2.f) + 0.5;

    RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void RotoZoom::DrawPixel(int x, int y, int offsetX, int offsetY, int angle, float scale)
{
    float sine = sineTable[angle % mathTableSize];
    float cosine = cosineTable[angle % mathTableSize];

    int texX = int((x * cosine - y * sine) / scale + offsetX) % texWidth;
    int texY = int((y * cosine + x * sine) / scale + offsetY) % texHeight;

    pixels[y * width + x] = texture[texY * texWidth + texX];
}

bool RotoZoom::Destroy()
{
    BMP::CloseRGBImage(texture);

    delete offsetPath;
    delete scaleAndAnglePath;
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}