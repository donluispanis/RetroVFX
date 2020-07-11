#ifdef __EMSCRIPTEN__
    #include <emscripten/emscripten.h>
    #include <emscripten/bind.h>
#endif

#include "FireDemo.h"

FireDemo fireDemo;

#ifdef __EMSCRIPTEN__
void main_loop()
{
    fireDemo.RenderFrame();
}

void forceInputUpdate(int key, bool isPressed)
{
    fireDemo.ForceKeyUpdate(key, isPressed);
}

EMSCRIPTEN_BINDINGS(input) 
{
    emscripten::function("forceInputUpdate", &forceInputUpdate);
}
#endif

int main()
{
    if (!fireDemo.Construct("Fire", 640, 360, false))
        return -1;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(&main_loop, -1, 1);
#else
    fireDemo.Run();
#endif

    fireDemo.Close();

    return 0;
}