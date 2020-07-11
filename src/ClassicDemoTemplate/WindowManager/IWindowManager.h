#pragma once

struct Pixel;

class IWindowManager
{
  public:
    virtual void CreateWindow(const char *name, const int width, const int height, const bool fullscreen, const bool forceFullscreen = false) = 0;
    virtual void DestroyWindow() = 0;
    virtual ~IWindowManager() = 0;

    virtual void UpdateWindow() = 0;
    virtual void DrawToScreen() = 0;

    virtual void SetFramerateToShow(bool fps) = 0;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual Pixel *GetScreenPixels() = 0;
    virtual double GetDeltaTime() = 0;
    virtual bool IsWindowOpen() = 0;

    virtual void RegisterKeyInput(int key) = 0;
    virtual bool IsKeyPressed(int key) = 0;
    virtual bool IsKeyHeld(int key) = 0;
    virtual bool IsKeyReleased(int key) = 0;
    virtual bool IsKeyUp(int key) = 0;
    virtual void ForceKeyUpdate(int key, bool isPressed) = 0;
};