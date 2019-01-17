#include <string>
#include <GLFW/glfw3.h>
#include "GLFWWindowManager.h"
#include "OpenGLRenderManager.h"
#include "Clock.h"

GLFWWindowManager::GLFWWindowManager()
{
    renderManager = nullptr;
    name = nullptr;
    height = 0;
    width = 0;
    window = nullptr;
    showFramerate = false;
    clock = new Clock();
    deltaTime = 0.0;
}

void GLFWWindowManager::CreateWindow(const char *name, const int width, const int height, const bool fullscreen)
{
    InitGLFW();
    SetOpenGLVersion();

    this->name = name;

    if (fullscreen)
    {
        CreateFullscrenWindow();
    }
    else
    {
        CreateRegularWindow(width, height);
    }

    AddGLFWOptions();

    renderManager = new OpenGLRenderManager();
    renderManager->InitialiseRender(this->width, this->height);
}

void GLFWWindowManager::InitGLFW()
{
    glfwInit();
}

void GLFWWindowManager::SetOpenGLVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

void GLFWWindowManager::CreateFullscrenWindow()
{
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
    window = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
}

void GLFWWindowManager::CreateRegularWindow(const int width, const int height)
{
    this->width = width;
    this->height = height;
    window = glfwCreateWindow(width, height, name, NULL, NULL);
}

void GLFWWindowManager::AddGLFWOptions()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void GLFWWindowManager::UpdateWindow()
{
    UpdateInput();
    UpdateTime();

    if(showFramerate)
    {
        glfwSetWindowTitle(window, std::string(std::string(name) + " - FPS: " + std::to_string(1 / deltaTime)).c_str());
    }
}

void GLFWWindowManager::UpdateInput()
{
    glfwPollEvents();

    int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void GLFWWindowManager::UpdateTime()
{
    deltaTime = clock->GetElapsedTime();
    clock->Reset();
}

void GLFWWindowManager::DrawToScreen()
{
    renderManager->DrawToScreen();
    glfwSwapBuffers(window);
}

void GLFWWindowManager::DestroyWindow()
{
    renderManager->DisposeRender();
    delete renderManager;

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWWindowManager::~GLFWWindowManager()
{
    delete clock;
}

void GLFWWindowManager::SetFramerateToShow(bool fps)
{
    showFramerate = fps;
}

int GLFWWindowManager::GetWidth()
{
    return width;
}

int GLFWWindowManager::GetHeight()
{
    return height;
}

Pixel* GLFWWindowManager::GetScreenPixels()
{
    return renderManager->GetScreenPixels();
}

double GLFWWindowManager::GetDeltaTime()
{
    return deltaTime;
}

bool GLFWWindowManager::IsWindowOpen()
{
    return glfwWindowShouldClose(window) == 0;
}