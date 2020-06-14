#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif

#include "PlanesDemo.h"

PlanesDemo p;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    p.RenderFrame();
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