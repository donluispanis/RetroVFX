#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif

#include "Deformations.h"

Deformations d;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    d.RenderFrame();
}
#endif

int main()
{
    if (!d.Construct("Deformations", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    d.Run();
#endif

    d.Close();

    return 0;
}