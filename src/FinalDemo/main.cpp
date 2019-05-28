#include "FinalDemo.h"

int main()
{
    FinalDemo f;
    if (!f.Construct("FinalDemo", 1280, 720, false, false))
        return -1;

    f.Run();
    f.Close();

    return 0;
}