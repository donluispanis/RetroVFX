#include "Deformations.h"

int main()
{

    Deformations d;
    if (!d.Construct("RotoZoom", 1280, 720, false))
        return -1;

    d.Run();
    d.Close();

    return 0;
}