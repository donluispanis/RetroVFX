#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "DotTunnelDemo.h"

DotTunnelDemo d;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    d.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    d.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{
    if (!d.Construct("DotTunnel", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    d.Run();
#endif

    d.Close();

    return 0;
}