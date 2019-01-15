#pragma once

#include "IWindowManager.h"

class GLFWwindow;

class GLFWWindowManager : public IWindowManager
{
  public:
    virtual void CreateWindow(const char *name, const int width, const int height, const bool fullscreen) override;
    virtual void DestroyWindow() override;

    virtual void UpdateInput() override;
    virtual void SwapBuffers() override;

    virtual void SetFPSToShow(bool fps) override { fps = showFramerate; };

    virtual int GetWidth() override { return width; };//WHAT do we do about this??
    virtual int GetHeight() override { return height; };
    

  private:
    void CreateFullscrenWindow();
    void CreateRegularWindow(const int width, const int height);

    void InitGLFW();
    void AddGLFWOptions();
    void SetOpenGLVersion();

    const char *name;
    int height;
    int width;
    GLFWwindow *window;
    bool showFramerate = true;
};