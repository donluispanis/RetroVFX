#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "RotoZoom.h"

RotoZoom r;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    r.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    r.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{

    if (!r.Construct("RotoZoom", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    r.Run();
#endif

    r.Close();

    return 0;
}