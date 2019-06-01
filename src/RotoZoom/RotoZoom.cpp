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

    InitMath();
    InitTurbulencePaths();

    if(!BMP::TryOpenImageInDifferentLocations("assets/img/lena.bmp", texture, texWidth, texHeight))
    {
        return false;
    }

    return true;
}

void RotoZoom::InitMath()
{
    mathTableSize = 2048;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);
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

bool RotoZoom::Destroy()
{
    BMP::CloseRGBImage(texture);
    Fast::DeleteMathTable(sineTable);
    Fast::DeleteMathTable(cosineTable);

    delete offsetPath;
    delete scaleAndAnglePath;

    return true;
}

bool RotoZoom::Update(float deltaTime)
{
    UpdatePath(deltaTime);

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            //We offset by 10000 units by default to avoid being close to the origin, where weird artifacts can happen
            DrawPixel(i, j, offsetX + 10000, offsetY + 10000, angle, scale);
        }
    }

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