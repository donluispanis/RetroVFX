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
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            DrawPixel(i, j, 0, 0, 0, 2.f);
        }
    }
    
    RenderText("Press space to change effect", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void RotoZoom::DrawPixel(int x, int y, int offsetX, int offsetY, int angle, float scale)
{
    int texX = int((x + offsetX)  * scale) % texWidth; 
    int texY = int((y + offsetY) * scale) % texHeight; 

    /** cosineTable[angle % mathTableSize]
* sineTable[angle % mathTableSize] **/

    pixels[y * width + x] = texture[texY * texWidth + texX];
}

bool RotoZoom::Destroy()
{
    BMP::CloseRGBImage(texture);

    delete [] sineTable;
    delete [] cosineTable;

    return true;
}