#pragma once

#include "IWindowManager.h"

class GLFWwindow;
class Clock;

class GLFWWindowManager : public IWindowManager
{
  public:
    GLFWWindowManager();
    virtual void CreateWindow(const char *name, const int width, const int height, const bool fullscreen) override;
    virtual void DestroyWindow() override;
    virtual ~GLFWWindowManager() override;

    virtual void UpdateWindow() override;
    virtual void SwapBuffers() override;

    virtual void SetFramerateToShow(bool fps) override;

    virtual int GetWidth() override;
    virtual int GetHeight() override;
    virtual double GetDeltaTime() override;
    virtual bool IsWindowOpen() override;
    

  private:
    void CreateFullscrenWindow();
    void CreateRegularWindow(const int width, const int height);

    void InitGLFW();
    void AddGLFWOptions();
    void SetOpenGLVersion();

    void UpdateInput();
    void UpdateTime();
    void ShowFramerateOnTitleWindow();

    const char *name;
    int height;
    int width;
    GLFWwindow *window;
    bool showFramerate;
    Clock* clock;
    double deltaTime;
};