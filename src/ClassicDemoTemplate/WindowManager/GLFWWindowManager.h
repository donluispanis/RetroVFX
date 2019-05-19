#pragma once

#include "IWindowManager.h"
#include "KeyState.h"
#include <map>

class GLFWwindow;
class Clock;
class IRenderManager;
struct Pixel;

class GLFWWindowManager : public IWindowManager
{
  public:
    GLFWWindowManager();
    virtual void CreateWindow(const char *name, const int width, const int height, const bool fullscreen, const bool forceFullscreen = false) override;
    virtual void DestroyWindow() override;
    virtual ~GLFWWindowManager() override;

    virtual void UpdateWindow() override;
    virtual void DrawToScreen() override;

    virtual void SetFramerateToShow(bool fps) override;

    virtual int GetWidth() override;
    virtual int GetHeight() override;
    virtual Pixel *GetScreenPixels() override;
    virtual double GetDeltaTime() override;
    virtual bool IsWindowOpen() override;

    virtual void RegisterKeyInput(int key) override;
    virtual bool IsKeyPressed(int key) override;
    virtual bool IsKeyHeld(int key) override;
    virtual bool IsKeyReleased(int key) override;
    virtual bool IsKeyUp(int key) override;

  private:
    void CreateForcedFullscreenWindow(const int width, const int height);
    void CreateFullscreenWindow();
    void CreateRegularWindow(const int width, const int height);

    void InitGLFW();
    void AddGLFWOptions();
    void SetOpenGLVersion();

    void UpdateInput();
    void UpdateKeyState(int state, KeyState& key);
    void UpdateTime();
    void ShowFramerateOnTitleWindow();

    IRenderManager *renderManager;

    std::map<int, KeyState> registeredKeyInput;

    const char *name;
    int height;
    int width;
    GLFWwindow *window;
    bool showFramerate;
    Clock *clock;
    double deltaTime;
};