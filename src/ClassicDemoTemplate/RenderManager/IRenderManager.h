#pragma once

struct Pixel;

class IRenderManager
{
    public:
        virtual void InitialiseRender(int width, int height) = 0;
        virtual void DisposeRender() = 0;
        virtual ~IRenderManager() = 0;

        virtual void DrawToScreen() = 0;

        virtual Pixel *GetScreenPixels() = 0;
};