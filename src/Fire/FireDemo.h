#include "../ClassicDemoTemplate.h"

class FireDemo : public ClassicDemoTemplate
{

  public:
    FireDemo(){};
    virtual ~FireDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float fDeltaTime) override;
    virtual bool Destroy() override;

    Pixel* pixels;
    int width, height;

    unsigned char* screenMapping;
    unsigned char* colourMap;
};