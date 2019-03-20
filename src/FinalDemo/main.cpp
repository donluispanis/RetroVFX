#include "FinalDemo.h"

int main()
{

    FinalDemo f;
    if (!f.Construct("Fire", 1280, 720, false))
        return -1;

    f.Run();
    f.Close();

    return 0;
}