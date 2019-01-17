#pragma once

class IRenderManager
{
    public:
        virtual void InitialiseRender(int width, int height, int channels) = 0;
        virtual void DisposeRender() = 0;

        virtual unsigned char *GetScreenData() = 0;
};