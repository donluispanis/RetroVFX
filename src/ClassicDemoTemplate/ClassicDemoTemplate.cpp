#include "ClassicDemoTemplate.h"
#include "WindowManager/IWindowManager.h"
#include "WindowManager/GLFWWindowManager.h"
#include "Characters.h"
#include "../Utils/Pixel.h"
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

    InitialiseText();

    if (!Init())
    {
        return false;
    }

    return true;
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

bool ClassicDemoTemplate::Close()
{
    windowManager->DestroyWindow();
    delete windowManager;

    delete [] characters;

    return Destroy();
}

void ClassicDemoTemplate::InitialiseText()
{
    characters = new char *[31];
    characters[0] = (char *)A;
    characters[1] = (char *)B;
    characters[2] = (char *)C;
    characters[3] = (char *)D;
    characters[4] = (char *)E;
    characters[5] = (char *)F;
    characters[6] = (char *)G;
    characters[7] = (char *)H;
    characters[8] = (char *)I;
    characters[9] = (char *)J;
    characters[10] = (char *)K;
    characters[11] = (char *)L;
    characters[12] = (char *)M;
    characters[13] = (char *)N;
    characters[14] = (char *)O;
    characters[15] = (char *)P;
    characters[16] = (char *)Q;
    characters[17] = (char *)R;
    characters[18] = (char *)S;
    characters[19] = (char *)T;
    characters[20] = (char *)U;
    characters[21] = (char *)V;
    characters[22] = (char *)W;
    characters[23] = (char *)X;
    characters[24] = (char *)Y;
    characters[25] = (char *)Z;
    characters[26] = (char *)exclamation;
    characters[27] = (char *)interrogation;
    characters[28] = (char *)apostrophe;
    characters[29] = (char *)comma;
    characters[30] = (char *)period;
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
        switch (c)
        {
        case '!':
            RenderCharacter(26, posX, posY, scale, colour);
            break;
        case '?':
            RenderCharacter(27, posX, posY, scale, colour);
            break;
        case '\'':
            RenderCharacter(28, posX, posY, scale, colour);
            break;
        case ',':
            RenderCharacter(29, posX, posY, scale, colour);
            break;
        case '.':
            RenderCharacter(30, posX, posY, scale, colour);
            break;
        default:
            RenderCharacter(c - 65, posX, posY, scale, colour);
            break;
        }
        posX += 6 * scale;
    }
}

void ClassicDemoTemplate::RenderCharacter(char character, int x, int y, int scale, const Pixel &colour)
{
    if (character < 0)
    {
        return;
    }

    Pixel *screen = windowManager->GetScreenPixels();
    int width = windowManager->GetWidth();

    for (int i = x; i < x + 5 * scale; i++)
    {
        for (int j = y; j < y + 5 * scale; j++)
        {
            int offsetX = (i - x) / scale;
            int offsetY = (j - y) / scale;

            if (characters[(int)character][offsetY * 5 + offsetX] != ' ')
            {
                screen[j * width + i] = colour;
            }
        }
    }
}