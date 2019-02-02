#include <cmath>
#include "TunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <iostream>

bool TunnelDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    GenerateTexture();
    GenerateTransformationTable();
    return true;
}

void TunnelDemo::GenerateTexture()
{
    tunnelTexture = new Pixel[width * height];
    int colourMapSize = width / 4;
    Pixel *colourMap = new Pixel[colourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::RAINBOW, colourMap, colourMapSize);

    int counter = 10;
    bool paintWhite = false;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (counter == 0 && paintWhite)
            {
                paintWhite = !paintWhite;
                counter = 10;
                break;
            }
            if (counter == 0 && !paintWhite)
            {
                paintWhite = !paintWhite;
                counter = 10;
                break;
            }
            if (paintWhite)
            {
                tunnelTexture[j * width + i] = colourMap[i % colourMapSize];
            }
            else
            {
                tunnelTexture[j * width + i] = Pixel();
            }
        }
        counter--;
    }

    delete[] colourMap;
}

void TunnelDemo::GenerateTransformationTable()
{
    distanceTable = new int[width * height];
    angleTable = new int[width * height];
    //generate non-linear transformation table
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int angle, distance;
            float ratio = 32.0;
            distance = int(ratio * height / sqrt((x - width / 2.0) * (x - width / 2.0) + (y - height / 2.0) * (y - height / 2.0))) % height;
            angle = (unsigned int)(0.5 * width * atan2(y - height / 2.0, x - width / 2.0) / 3.1416);
            distanceTable[y * width + x] = distance;
            angleTable[y * width + x] = angle;
        }
    }
}

bool TunnelDemo::Update(float deltaTime)
{
    static float animation = 0.0f;
    animation += windowManager->GetDeltaTime();
    //calculate the shift values out of the animation value
    int shiftX = animation * 40;
    int shiftY = animation * 40;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int i = ((unsigned int)(distanceTable[y * width + x] + shiftX)) % width;
            int j = ((unsigned int)(angleTable[y * width + x] + shiftY)) % height;
            ////get the texel from the texture by using the tables, shifted with the animation values
            Pixel color = tunnelTexture[j * width + i];
            pixels[y * width + x] = color;
        }
    }
    RenderText("Tunnel effect.", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

bool TunnelDemo::Destroy()
{
    delete[] tunnelTexture;
    delete[] distanceTable;
    delete[] angleTable;

    return true;
}