#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "PlasmaDemo.h"

PlasmaDemo plasmaDemo;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    plasmaDemo.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    plasmaDemo.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{
    if (!plasmaDemo.Construct("Plasma", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    plasmaDemo.Run();
#endif

    plasmaDemo.Close();

    return 0;
}