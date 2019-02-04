#include "RotoZoom.h"

int main()
{

    RotoZoom r;
    if (!r.Construct("RotoZoom", 1280, 720, false))
        return -1;

    r.Run();
    r.Close();

    return 0;
}