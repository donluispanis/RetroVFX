#include "DotTunnelDemo.h"

int main()
{

    DotTunnelDemo d;
    if (!d.Construct("DotTunnel", 1280, 720, false))
        return -1;

    d.Run();
    d.Close();

    return 0;
}