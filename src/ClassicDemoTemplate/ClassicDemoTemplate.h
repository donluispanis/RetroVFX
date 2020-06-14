#pragma once

class IWindowManager;
class Clock;
struct Pixel;

class ClassicDemoTemplate
{
  public:
    ClassicDemoTemplate();
    virtual ~ClassicDemoTemplate();

    bool Construct(const char *name, const int width, const int height, const bool fullscreen, const bool forceFullscreen = false);
    void Run();
    void RenderFrame();
    bool Close();
    void main_loop();

    IWindowManager *GetWindowManager() { return windowManager; }
    void RenderText(const char *text, int posX, int posY, int scale, const Pixel &colour);
    void RenderDot(int x, int y, const Pixel &colour, int dotSize);
    void RenderLine(int x1, int y1, int x2, int y2, const Pixel &colour, const int thickness);
    void RenderLine(int x1, int y1, int x2, int y2, const Pixel &colour1, const Pixel &colour2, const int thickness);
    void ClearScreen(const Pixel &colour);
    void ClearScreen(int x1, int y1, int x2, int y2, const Pixel &colour);
    bool IsPixelOutOfBounds(int x, int y);

  private:
    //Functions that have to be overwritten by the implementation
    virtual bool Init() = 0;                  //Init demo specific related variables
    virtual bool Update(float deltaTime) = 0; //Update demo specific related variables
    virtual bool Destroy() = 0;               //Destroys, if necessary, variables created on init

    void UpdateInput();
    void UpdateTime();

    void DrawLineWithSmallSlope(int x1, int y1, int x2, int y2, const Pixel &colour1, const Pixel &colour2, float slope, const int thickness);
    void DrawLineWithBigSlope(int x1, int y1, int x2, int y2, const Pixel &colour1, const Pixel &colour2, float slope, const int thickness);
    float GetSlope(int x1, int y1, int x2, int y2);
    void GetSigns(int x1, int y1, int x2, int y2, int &signX, int &signY);
    Pixel GetInterpolatedColour(int p1, int p2, int pAux, const Pixel &colour1, const Pixel &colour2);

    void RenderCharacter(char character, int x, int y, int scale, const Pixel &colour);

    IWindowManager *windowManager;

    int width, height;
    Pixel *screen;
};