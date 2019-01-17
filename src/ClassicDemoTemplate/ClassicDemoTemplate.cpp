#include "ClassicDemoTemplate.h"
#include "GLFWWindowManager.h"

//Window, Engine and OpenGL initialization
bool ClassicDemoTemplate::Construct(const char *name, const int width, const int height, const bool fullscreen)
{

    windowManager = new GLFWWindowManager();
    windowManager->CreateWindow(name, width, height, fullscreen);
    windowManager->SetFramerateToShow(true);

    if (!Init()){}
        //return ShowError("Failed to execute user defined Init function");

    return true;
}

//Engine basic update
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

//Window and variables deletion
bool ClassicDemoTemplate::Close()
{
    bool ret = Destroy(); //Destroy function defined by the user

    windowManager->DestroyWindow();
    delete windowManager;

    return ret;
}
