#pragma once

#include "IRenderManager.h"

struct Pixel;

class OpenGLRenderManager : public IRenderManager
{
  public:
    virtual void InitialiseRender(int width, int height) override;
    virtual void DisposeRender() override;
    virtual ~OpenGLRenderManager() override;

    virtual void DrawToScreen() override;

    virtual Pixel *GetScreenPixels() override;

  private:
    void InitGlew();
    void InitOpenGL();
    void CreateVAOandVBO();
    void CreateElementBuffers();
    void CreateOpenGLProgram();
    void SetShaderVariables();
    void SetTexture();
    const char *GetVertexShader();
    const char *GetFragmentShader();

    Pixel *screenPixels;

    unsigned int textureID;
    unsigned int programID;

    int width;
    int height;
    const int channels = 3;
};