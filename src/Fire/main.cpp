#include "../ClassicDemoTemplate.h"
#include <iostream>
class Fire : public ClassicDemoTemplate
{

  public:
    Fire(){};
    virtual ~Fire(){};

  private:
    //Functions that have to be overwritten by the implementation
    virtual bool Init() { return true; };                   //Init demo specific related variables
    virtual bool Update(float fDeltaTime) { return true; }; //Update demo specific related variables
    virtual bool Destroy() { return true; };                //Destroys, if necessary, variables created on init
};

int main()
{

    Fire f;
    if (!f.Construct("Fire", 1280, 720, false))
        return -1;

    f.Run(10);

    return 0;
}