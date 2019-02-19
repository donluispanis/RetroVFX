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
    void RenderDot(int x, int y, const Pixel &colour, int dotSize);
    void RenderLine(int x1, int y1, int x2, int y2, const Pixel &colour);
    void ClearScreen(const Pixel &colour);
    bool IsPixelOutOfBounds(int x, int y);

  private:
    //Functions that have to be overwritten by the implementation
    virtual bool Init() = 0;                  //Init demo specific related variables
    virtual bool Update(float deltaTime) = 0; //Update demo specific related variables
    virtual bool Destroy() = 0;               //Destroys, if necessary, variables created on init

    void UpdateInput();
    void UpdateTime();

    void DrawLineWithSmallSlope(int x1, int y1, int x2, int y2, const Pixel &colour, float slope);
    void DrawLineWithBigSlope(int x1, int y1, int x2, int y2, const Pixel &colour, float slope);
    float GetSlope(int x1, int y1, int x2, int y2);
    void GetSigns(int x1, int y1, int x2, int y2, int &signX, int &signY);

    void RenderCharacter(char character, int x, int y, int scale, const Pixel &colour);

    IWindowManager *windowManager;

    int width, height;
    Pixel *screen;
};