#include "ClassicDemoTemplate.h"
#include "WindowManager/IWindowManager.h"
#include "WindowManager/GLFWWindowManager.h"

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

    return Destroy();
}
