#pragma once

class IWindowManager;
class Clock;
struct Pixel;

class ClassicDemoTemplate
{
  public:
    ClassicDemoTemplate();
    virtual ~ClassicDemoTemplate();

    bool Construct(const char *name, const int width, const int height, const bool fullscreen);
    void Run();
    bool Close();

    IWindowManager *GetWindowManager() { return windowManager; }
    void RenderText(const char *text, int posX, int posY, int scale, const Pixel &colour);

  private:
    //Functions that have to be overwritten by the implementation
    virtual bool Init() = 0;                  //Init demo specific related variables
    virtual bool Update(float deltaTime) = 0; //Update demo specific related variables
    virtual bool Destroy() = 0;               //Destroys, if necessary, variables created on init

    void InitialiseText();
    void UpdateInput();
    void UpdateTime();

    void RenderCharacter(char character, int x, int y, int scale, const Pixel &colour);

    IWindowManager *windowManager;
    Clock *clock;
    char **characters;
};