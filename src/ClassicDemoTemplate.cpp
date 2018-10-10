#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

#include "ClassicDemoTemplate.h"

//Window, Engine and OpenGL initialization
bool ClassicDemoTemplate::Construct(const char *name, const int width, const int height, const bool fullscreen)
{
    if (!glfwInit())
       return ShowError("Failed to initialize GLFW");

    SetOpenGLVersion();
    SetWindowName(name);

    if (fullscreen)
        CreateFullscrenWindow();
    else 
        CreateWindow(width, height);

    if (window == NULL)
        return ShowError("Failed to open GLFW window");

    AddGLFWOptions();
    InitEngineData();

    if (!Init())
        return ShowError("Failed to execute user defined Init function");

    return true;
}

void ClassicDemoTemplate::SetOpenGLVersion() 
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

void ClassicDemoTemplate::SetWindowName(const char* name)
{
    this->name = name;
}

void ClassicDemoTemplate::CreateFullscrenWindow()
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPhysicalSize(monitor, &this->width, &this->height);
    window = glfwCreateWindow(this->width, this->height, name, monitor, NULL);
}

void ClassicDemoTemplate::CreateWindow(const int width, const int height)
{
    this->width = width;
    this->height = height;

    window = glfwCreateWindow(width, height, name, NULL, NULL);
}

bool ClassicDemoTemplate::AddGLFWOptions()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

bool ClassicDemoTemplate::InitEngineData()
{
    screenData = new unsigned char[this->width * this->height * 3];

    clockOld = std::chrono::system_clock::now();
    clockNow = clockOld;
    fDeltaTime = 0.f;
}

bool ClassicDemoTemplate::ShowError(const char* message)
{
    std::cerr << message << std::endl;
    glfwTerminate();
    return false;
}

//Engine basic update
void ClassicDemoTemplate::Run(float framerate, float duration)
{
    while (glfwWindowShouldClose(window) == 0)
    {
        SetScreenBlack();
        UpdateInput();
        UpdateTime();

        if (!Update(fDeltaTime))
            return; //Update function defined by the user

        DrawToScreen();
    }
}

void ClassicDemoTemplate::SetScreenBlack()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClassicDemoTemplate::UpdateInput()
{
    glfwPollEvents();

    int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void ClassicDemoTemplate::UpdateTime()
{
    clockOld = clockNow;
    clockNow = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed_seconds = clockNow - clockOld;
    fDeltaTime = elapsed_seconds.count();
}

void ClassicDemoTemplate::DrawToScreen()
{
    glfwSwapBuffers(window);
}

//Window and variables deletion
bool ClassicDemoTemplate::Close()
{
    bool ret = Destroy(); //Destroy function defined by the user

    delete[] screenData;

    glfwDestroyWindow(window);
    glfwTerminate();

    return ret;
}
