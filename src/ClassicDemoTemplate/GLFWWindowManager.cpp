#include <GLFW/glfw3.h>
#include "GLFWWindowManager.h"

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

void GLFWWindowManager::UpdateInput()
{
    glfwPollEvents();

    int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}

void GLFWWindowManager::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void GLFWWindowManager::DestroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}