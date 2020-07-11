#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "PlanesDemo.h"

PlanesDemo p;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    p.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    p.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{

    if (!p.Construct("Planes", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    p.Run();
#endif

    p.Close();

    return 0;
}