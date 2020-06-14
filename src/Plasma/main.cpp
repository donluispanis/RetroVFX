#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif

#include "PlasmaDemo.h"

PlasmaDemo plasmaDemo;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    plasmaDemo.RenderFrame();
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