#include "RotoZoom.h"
#include "../Utils/Pixel.h"
#include "../Utils/BMP.h"
#include "../Utils/Fast.h"
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

    BMP::OpenRGBImage("assets/img/lena.bmp", texture, texWidth, texHeight);

    return true;
}

bool RotoZoom::Update(float deltaTime)
{
    static int offsetX = 0;
    static int offsetY = 0;
    static int angle = 0;
    static float scale = 1;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            DrawPixel(i, j, offsetX, offsetY, angle, scale);
        }
    }
    offsetX++;
    offsetY++;
    angle++;
    angle++;
    angle++;
    angle++;
    scale += 0.1;

    RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void RotoZoom::DrawPixel(int x, int y, int offsetX, int offsetY, int angle, float scale)
{
    float sine = sineTable[angle % mathTableSize];
    float cosine = cosineTable[angle % mathTableSize];

    int texX = (x + offsetX) / scale;
    int texY = (y + offsetY) / scale;

    texX = int(x * cosine - y * sine) % texWidth;
    texY = int(y * cosine + x * sine) % texHeight;

    pixels[y * width + x] = texture[texY * texWidth + texX];
}

bool RotoZoom::Destroy()
{
    BMP::CloseRGBImage(texture);

    delete[] sineTable;
    delete[] cosineTable;

    return true;
}