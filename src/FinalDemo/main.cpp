#include "FinalDemo.h"

int main()
{
    FinalDemo f;
    if (!f.Construct("Fire", 1280, 720, true))
        return -1;

    f.Run();
    f.Close();

    return 0;
}