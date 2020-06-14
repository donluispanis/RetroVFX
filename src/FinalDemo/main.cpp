#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
#endif

#include "FinalDemo.h"

FinalDemo f;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    f.RenderFrame();
}
#endif

int main()
{
    if (!f.Construct("FinalDemo", 640, 360, false, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    f.Run();
#endif

    f.Close();

    return 0;
}