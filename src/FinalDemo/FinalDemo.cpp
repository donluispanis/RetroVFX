#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

#include "Imp/Imp_Audio.cpp"
#include "Imp/Imp_Fire.cpp"
#include "Imp/Imp_Geometry.cpp"

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    InitAudio();
    InitFire();
    InitGeometry();

    return true;
}

bool FinalDemo::Destroy()
{
    CloseAudio();
    CloseFire();
    CloseGeometry();

    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    /** Fire
    **/
    ClearScreen(Pixel(0));
    for (int j = height / 2 - 2; j >= 0; j--)
    {
        for (int i = 0, n = width / 2; i < n; i++)
        {
            int index = j * n + i;
            int rowBelow = index + n;

            if (fireMapping[rowBelow] != 0)
            {
                screenMapping[rowBelow] = 255;
            }

            int colourIndex = (screenMapping[rowBelow + 1] + screenMapping[rowBelow] + screenMapping[rowBelow - 1]) / (3.1) + (Fast::Rand() % 3 == 0 ? 1 : 0);
            screenMapping[index] = colourIndex;
            RenderDot(i * 2, j * 2, colourMap[colourIndex], 2);
        }
    }

    /** Geometry
    EraseObject(grid);
    ApplyObjectTransformations(deltaTime);
    GeneratePerspectiveProjection(grid);
    RenderObject(grid);
    UndoObjectTransformations(deltaTime);
    **/
    return true;
}