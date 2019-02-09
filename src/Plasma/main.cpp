#include "PlasmaDemo.h"

int main()
{

    PlasmaDemo p;
    if (!p.Construct("Plasma", 1280, 720, false))
        return -1;

    p.Run();
    p.Close();

    return 0;
}