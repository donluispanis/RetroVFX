#include "RotoZoom.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
#include "../Utils/TurbulencePath.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>

bool RotoZoom::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    InitMath();
    InitTurbulencePaths();

    BMP::OpenRGBImage("assets/img/lena.bmp", texture, texWidth, texHeight);

    return true;
}

void RotoZoom::InitMath()
{
    mathTableSize = 2048;
    sineTable = new float[mathTableSize];
    Fast::GenerateSineTable(sineTable, mathTableSize);
    cosineTable = new float[mathTableSize];
    Fast::GenerateCosineTable(cosineTable, mathTableSize);
}

void RotoZoom::InitTurbulencePaths()
{
    offsetPath = new TurbulencePath(sineTable, cosineTable, mathTableSize);
    scaleAndAnglePath = new TurbulencePath(sineTable, cosineTable, mathTableSize);

    offsetPath->CreateTurbulencePath(6, height, 4);
    offsetPath->UpdateTurbulencePath(200, offsetX, offsetY);

    scaleAndAnglePath->CreateTurbulencePath(4, height, 4);
    scaleAndAnglePath->UpdateTurbulencePath(200, scale, angle);
}

bool RotoZoom::Update(float deltaTime)
{
    UpdatePath(deltaTime);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //We offset by 10000 units by default to avoid being close to the origin, where weird artifacts can happens
            DrawPixel(i, j, offsetX + 10000, offsetY + 10000, angle, scale);
        }
    }

    //RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void RotoZoom::UpdatePath(float deltaTime)
{
    offsetPath->UpdateTurbulencePath(deltaTime, offsetX, offsetY);
    scaleAndAnglePath->UpdateTurbulencePath(deltaTime, scale, angle);
    scale = scale / (height) + 1.f;
    angle = Fast::Abs(angle) * 2.f;
}

void RotoZoom::DrawPixel(int x, int y, int offsetX, int offsetY, int angle, float scale)
{
    float sine = sineTable[angle % mathTableSize];
    float cosine = cosineTable[angle % mathTableSize];

    int texX = Fast::Abs(int((x * cosine - y * sine) / scale + offsetX)) % texWidth;
    int texY = Fast::Abs(int((y * cosine + x * sine) / scale + offsetY)) % texHeight;

    pixels[y * width + x] = texture[texY * texWidth + texX];
}

void RotoZoom::DrawPixelWave(int x, int y)
{

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