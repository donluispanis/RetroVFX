#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif

#include "RotoZoom.h"

RotoZoom r;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    r.RenderFrame();
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