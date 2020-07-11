#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #define GLFW_INCLUDE_ES3
#endif

#include <string>
#include <GLFW/glfw3.h>
#include "GLFWWindowManager.h"
#include "../RenderManager/OpenGLRenderManager.h"
#include "../../Utils/Clock.h"
#include <iostream>

void OutputErrorCode(bool error, const char* errorText)
{
    if(error == 0)
    {
        std::cout << "GLFW error: " << errorText << std::endl;
    }
}

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

GLFWWindowManager::~GLFWWindowManager()
{
    delete clock;
}

#ifdef __EMSCRIPTEN__
// This method updates the states variable, that holds the state for all the keys in the virtual keyboard
// and which is defined in the base_html.html
EM_JS(void, InitWASMInput, (), {
    var onPressed = (ev) =>
    {
      let id = ev.target.id;

      if(states[id] == undefined)
      {
        return;
      }

      states[id] = true;
    };

    var onReleased = (ev) =>
    {
      let id = ev.target.id;

      if(states[id] == undefined)
      {
        return;
      }

      states[id] = false;
    };

    document.addEventListener("mousedown", onPressed);
    document.addEventListener("touchstart", onPressed);

    document.addEventListener("mouseup", onReleased);
    document.addEventListener("touchend", onReleased);
});
#endif

void GLFWWindowManager::CreateWindow(const char *name, const int width, const int height, const bool fullscreen, const bool forceFullscreen)
{
    InitGLFW();
    SetOpenGLVersion();

    this->name = name;

    if (forceFullscreen)
    {
        CreateForcedFullscreenWindow(width, height);
    }
    else if (fullscreen)
    {
        CreateFullscreenWindow();
    }
    else
    {
        CreateRegularWindow(width, height);
    }

    AddGLFWOptions();

    renderManager = new OpenGLRenderManager();
    renderManager->InitialiseRender(this->width, this->height);

    clock->Reset();

#ifdef __EMSCRIPTEN__
    InitWASMInput();
#endif
}

void GLFWWindowManager::InitGLFW()
{
    OutputErrorCode(glfwInit(), "could not init GLFW");
}

void GLFWWindowManager::SetOpenGLVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

void GLFWWindowManager::CreateForcedFullscreenWindow(const int width, const int height)
{
    this->width = width;
    this->height = height;

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width, mode->height, name, glfwGetPrimaryMonitor(), NULL);

    OutputErrorCode(window, "could not open window");
}

void GLFWWindowManager::CreateFullscreenWindow()
{
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
    window = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);

    OutputErrorCode(window, "could not open window");
}

void GLFWWindowManager::CreateRegularWindow(const int width, const int height)
{
    this->width = width;
    this->height = height;
    window = glfwCreateWindow(width, height, name, NULL, NULL);

    OutputErrorCode(window, "could not open window");
}

void GLFWWindowManager::AddGLFWOptions()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
}

void GLFWWindowManager::UpdateWindow()
{
    UpdateInput();
    UpdateTime();

    if (showFramerate)
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

    for (auto &key : registeredKeyInput)
    {
        int state = glfwGetKey(window, key.first);
        UpdateKeyState(state, key.second);
    }

#ifdef __EMSCRIPTEN__
    EM_ASM(
        for(let i in states)
        {
            // This javascript piece will then call C++ code, forcing an input update synchonized with the framerate
            // This method needs to be bound in the main, and will call the ClassicDemoTemplate::ForceKeyUpdate
            // method which will subsequently call GLFWWindowManager::ForceKeyUpdate
            // The keys and states variables are declared in base_html.html
            Module.forceInputUpdate(keys[i], states[i]);
        }
    );
#endif
}

void GLFWWindowManager::UpdateKeyState(int state, KeyState &key)
{
    if (state == GLFW_PRESS && (!key.isPressed && !key.isHeld))
    {
        key.isPressed = true;
    }
    else if (state == GLFW_PRESS)
    {
        key.isPressed = false;
        key.isHeld = true;
    }

    if (state != GLFW_PRESS && (key.isHeld || key.isPressed))
    {
        key.isPressed = false;
        key.isHeld = false;
        key.isReleased = true;
    }
    else if (state != GLFW_PRESS)
    {
        key.isReleased = false;
        key.isUp = true;
    }
}

void GLFWWindowManager::ForceKeyUpdate(int key, bool isPressed)
{
    if(registeredForcedKeyInput.find(key) == registeredForcedKeyInput.end())
    {
        return;
    }

    UpdateKeyState(
        isPressed ? GLFW_PRESS : GLFW_RELEASE,
        registeredForcedKeyInput[key]);
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

Pixel *GLFWWindowManager::GetScreenPixels()
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

void GLFWWindowManager::RegisterKeyInput(int key)
{
    registeredKeyInput[key] = KeyState();
    registeredForcedKeyInput[key] = KeyState();
}

bool GLFWWindowManager::IsKeyPressed(int key)
{
    const auto &keyState = registeredKeyInput.find(key);
    const auto &forcedKeyState = registeredForcedKeyInput.find(key);

    if (keyState != registeredKeyInput.cend())
    {
        return keyState->second.isPressed
            || forcedKeyState->second.isPressed;
    }

    return false;
}

bool GLFWWindowManager::IsKeyHeld(int key)
{
    const auto &keyState = registeredKeyInput.find(key);
    const auto &forcedKeyState = registeredForcedKeyInput.find(key);

    if (keyState != registeredKeyInput.cend())
    {
        return keyState->second.isHeld
            || forcedKeyState->second.isHeld;
    }

    return false;
}

bool GLFWWindowManager::IsKeyReleased(int key)
{
    const auto &keyState = registeredKeyInput.find(key);
    const auto &forcedKeyState = registeredForcedKeyInput.find(key);

    if (keyState != registeredKeyInput.cend())
    {
        return keyState->second.isReleased
            || forcedKeyState->second.isReleased;
    }

    return false;
}

bool GLFWWindowManager::IsKeyUp(int key)
{
    const auto &keyState = registeredKeyInput.find(key);
    const auto &forcedKeyState = registeredForcedKeyInput.find(key);

    if (keyState != registeredKeyInput.cend())
    {
        return keyState->second.isUp
            && forcedKeyState->second.isUp;
    }

    return false;
}