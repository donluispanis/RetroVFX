#include "../ClassicDemoTemplate.h"
#include <iostream>
class Fire : public ClassicDemoTemplate
{

  public:
    Fire(){};
    virtual ~Fire(){};

  private:
    float acc = 100;
    //Functions that have to be overwritten by the implementation
    virtual bool Init()
    {
        return true;
    }; //Init demo specific related variables
    virtual bool Update(float fDeltaTime)
    {
        acc += fDeltaTime;
        if (acc > 100)
        {
            for (int i = GetWidth() * (GetHeight() - 1); i < GetWidth() * GetHeight(); i++)
            {
                GetScreenPixels()[i].Clear();
                if (rand() % 2 == 0)
                    GetScreenPixels()[i] = Pixel(255, 0, 0);
            }
            acc = 0;
        }

        for (int i = GetWidth() * (GetHeight() - 1); i >= 0; i--)
        {
            GetScreenPixels()[i] = Pixel(
                (GetScreenPixels()[i + 1 + GetWidth()].R + GetScreenPixels()[i + GetWidth()].R + GetScreenPixels()[i - 1 + GetWidth()].R) / 3 + (rand() % 10 == 0 ? 1 : 0),
                0,
                0);
        }
        return true;
    };                                       //Update demo specific related variables
    virtual bool Destroy() { return true; }; //Destroys, if necessary, variables created on init
};

int main()
{

    Fire f;
    if (!f.Construct("Fire", 1280, 720, false))
        return -1;

    f.Run(1000);

    return 0;
}