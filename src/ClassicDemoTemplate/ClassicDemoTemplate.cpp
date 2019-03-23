#include "ClassicDemoTemplate.h"
#include "WindowManager/IWindowManager.h"
#include "WindowManager/GLFWWindowManager.h"
#include "Characters/Characters.h"
#include "../Utils/Pixel.h"
#include "../Utils/Fast.h"
#include <string>

ClassicDemoTemplate::ClassicDemoTemplate()
{
}

ClassicDemoTemplate::~ClassicDemoTemplate()
{
}

//Window, Engine and OpenGL initialization
bool ClassicDemoTemplate::Construct(const char *name, const int width, const int height, const bool fullscreen)
{
    windowManager = new GLFWWindowManager();
    windowManager->CreateWindow(name, width, height, fullscreen);

    this->width = windowManager->GetWidth();
    this->height = windowManager->GetHeight();
    this->screen = windowManager->GetScreenPixels();

    if (!Init())
    {
        return false;
    }

    return true;
}

bool ClassicDemoTemplate::Close()
{
    windowManager->DestroyWindow();
    delete windowManager;

    return Destroy();
}

void ClassicDemoTemplate::Run()
{
    while (windowManager->IsWindowOpen())
    {
        double dt = windowManager->GetDeltaTime();
        windowManager->UpdateWindow();

        if (!Update(dt))
        {
            return;
        }

        windowManager->DrawToScreen();
    }
}

void ClassicDemoTemplate::RenderText(const char *text, int posX, int posY, int scale, const Pixel &colour)
{
    std::string txt(text);
    for (auto &c : txt)
    {
        c = toupper(c);
    }

    for (auto c : txt)
    {
        RenderCharacter(c, posX, posY, scale, colour);
        posX += 6 * scale;
    }
}

void ClassicDemoTemplate::RenderCharacter(char character, int x, int y, int scale, const Pixel &colour)
{
    if (character < 0 || character == ' ')
    {
        return;
    }

    const char *c = Characters::GetCharactersMap()[character];

    for (int i = x; i < x + 5 * scale; i++)
    {
        for (int j = y; j < y + 5 * scale; j++)
        {
            int offsetX = (i - x) / scale;
            int offsetY = (j - y) / scale;

            if (c[offsetY * 5 + offsetX] != ' ')
            {
                screen[j * width + i] = colour;
            }
        }
    }
}

void ClassicDemoTemplate::RenderDot(int x, int y, const Pixel &colour, int dotSize)
{
    for (int i = 0; i < dotSize; i++)
    {
        for (int j = 0; j < dotSize; j++)
        {
            int offsetX = x + i;
            int offsetY = y + j;

            if (IsPixelOutOfBounds(offsetX, offsetY))
            {
                continue;
            }

            screen[offsetY * width + offsetX] = colour;
        }
    }
}

void ClassicDemoTemplate::RenderLine(int x1, int y1, int x2, int y2, const Pixel &colour, const int thickness)
{
    //Calculate the slope of the line to be drawn
    float slope = GetSlope(x1, y1, x2, y2);

    //Slope < 45º
    if (Fast::Abs(slope) <= 1.f && Fast::Abs(slope) >= 0.f)
    {
        DrawLineWithSmallSlope(x1, y1, x2, y2, colour, slope, thickness);
    }
    //Slope > 45º
    else if (Fast::Abs(slope) > 1.f)
    {
        DrawLineWithBigSlope(x1, y1, x2, y2, colour, slope, thickness);
    }
}

void ClassicDemoTemplate::DrawLineWithSmallSlope(int x1, int y1, int x2, int y2, const Pixel &colour, float slope, const int thickness)
{
    float acummulated = 0.f;  //When this hits 1, we make 1 pixel increment
    int auxX = x1, auxY = y1; //auxiliar point that we will increment from the old point to the new one

    int signX, signY;
    GetSigns(x1, y1, x2, y2, signX, signY);

    //While we don't reach the desired pixel position
    while (auxX != x2 || auxY != y2)
    {
        RenderDot(auxX, auxY, colour, thickness);

        if (auxX != x2)
        {
            auxX += signX; //Increment X until it reaches the target
        }

        acummulated += Fast::Abs(slope); //When this reaches 1, we increment Y

        if (acummulated >= 1.f)
        {
            auxY += signY;
            acummulated -= 1.f;
        }
    }
}

void ClassicDemoTemplate::DrawLineWithBigSlope(int x1, int y1, int x2, int y2, const Pixel &colour, float slope, const int thickness)
{
    float acummulated = 0.f;  //When this hits 1, we make 1 pixel increment
    int auxX = x1, auxY = y1; //auxiliar point that we will increment from the old point to the new one

    int signX, signY;
    GetSigns(x1, y1, x2, y2, signX, signY);

    //While we don't reach the desired pixel position
    while (auxX != x2 || auxY != y2)
    {
        RenderDot(auxX, auxY, colour, thickness);

        if (auxY != y2)
            auxY += signY;                   //Increment Y until it reaches the target
        acummulated += 1 / Fast::Abs(slope); //When this reaches 1, we increment X

        if (acummulated >= 1.f)
        {
            auxX += signX;
            acummulated -= 1.f;
        }
    }
}

float ClassicDemoTemplate::GetSlope(int x1, int y1, int x2, int y2)
{
    return (float)(y2 - y1) / (float)(x2 - x1);
}

void ClassicDemoTemplate::GetSigns(int x1, int y1, int x2, int y2, int &signX, int &signY)
{
    signX = (x2 - x1) >= 0 ? 1 : -1; //Calculate X direction
    signY = (y2 - y1) >= 0 ? 1 : -1; //Calculate Y direction
}

void ClassicDemoTemplate::ClearScreen(const Pixel &colour)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            screen[j * width + i] = colour;
        }
    }
}

void ClassicDemoTemplate::ClearScreen(int x1, int y1, int x2, int y2, const Pixel &colour)
{
    int nx1 = x1 < x2 ? x1 : x2;
    int nx2 = x2 > x1 ? x2 : x1;
    int ny1 = y1 < y2 ? y1 : y2;
    int ny2 = y2 > y1 ? y2 : y1;

    if (nx1 < 0)
    {
        nx1 = 0;
    }
    if (nx2 > width)
    {
        nx2 = width;
    }
    if (ny1 < 0)
    {
        ny1 = 0;
    }
    if (ny2 > height)
    {
        ny2 = 0;
    }

    for (int i = nx1; i < nx2; i++)
    {
        for (int j = ny1; j < ny2; j++)
        {
            screen[j * width + i] = colour;
        }
    }
}

bool ClassicDemoTemplate::IsPixelOutOfBounds(int x, int y)
{
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
    {
        return true;
    }
    return false;
}