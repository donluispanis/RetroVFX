#include "Geometry.h"

int main()
{

    GeometryDemo g;
    if (!g.Construct("Fire", 1280, 720, false))
        return -1;

    g.Run();
    g.Close();

    return 0;
}