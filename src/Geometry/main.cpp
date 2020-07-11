#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "Geometry.h"

GeometryDemo g;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    g.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    g.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{

    if (!g.Construct("Geometry", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    g.Run();
#endif

    g.Close();

    return 0;
}