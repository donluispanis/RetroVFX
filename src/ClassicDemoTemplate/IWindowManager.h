#pragma once

class IWindowManager
{
  public:
    virtual void CreateWindow(const char *name, const int width, const int height, const bool fullscreen) = 0;
    virtual void DestroyWindow() = 0;

    virtual void UpdateInput() = 0;
    virtual void SwapBuffers() = 0;

    virtual void SetFPSToShow(bool fps) = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
};