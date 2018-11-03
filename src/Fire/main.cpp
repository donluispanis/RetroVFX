#include "FireDemo.h"

int main()
{

    FireDemo f;
    if (!f.Construct("Fire", 1280, 720, false))
        return -1;

    f.Run();
    f.Close();

    return 0;
}