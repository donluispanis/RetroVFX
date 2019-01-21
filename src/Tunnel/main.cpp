#include "TunnelDemo.h"

int main()
{

    TunnelDemo f;
    if (!f.Construct("Tunnel", 1280, 720, false))
        return -1;

    f.Run();
    f.Close();

    return 0;
}