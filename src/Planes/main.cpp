#include "PlanesDemo.h"

int main()
{

    PlanesDemo p;
    if (!p.Construct("Planes", 1280, 720, false))
        return -1;

    p.Run();
    p.Close();

    return 0;
}