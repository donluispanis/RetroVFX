#include "PaintLike.h"

int main()
{

    PaintLike p;

    if(!p.Init(1280,720))
        return -1;
        
    p.Run();

    return 0;
}