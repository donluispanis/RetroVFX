#include "DotTunnelDemo.h"

int main()
{

    DotTunnelDemo f;
    if (!f.Construct("DotTunnel", 1280, 720, true))
        return -1;

    f.Run();
    f.Close();

    return 0;
}