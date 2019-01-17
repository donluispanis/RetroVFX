#pragma once

#include "IRenderManager.h"

class Pixel;

class OpenGLRenderManager : public IRenderManager
{
  public:
    virtual void InitialiseRender(int width, int height, int channels) override;
    virtual void DisposeRender() override;

    virtual unsigned char *GetScreenData() override;

    private:

    union {
        unsigned char *screenData;
        Pixel *screenPixels;
    };

    unsigned int textureID;
    unsigned int programID;
};