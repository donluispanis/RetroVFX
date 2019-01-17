#pragma once

class IWindowManager;
class Clock;

class ClassicDemoTemplate
{
  public:
    ClassicDemoTemplate() {}
    virtual ~ClassicDemoTemplate() {}

    //Basic use functions
    bool Construct(const char *name, const int width, const int height, const bool fullscreen); //Creates a screen using OpenGL and provides a mode of accesing pixels
    void Run();                                                                                 //Starts the application
    bool Close();                                                                               //Destroys the window and the pixel data

    //Getters
    IWindowManager *GetWindowManager() { return windowManager; }

    //Setters
    bool ShowError(const char *message);

  private:
    //Functions that have to be overwritten by the implementation
    virtual bool Init() = 0;                  //Init demo specific related variables
    virtual bool Update(float deltaTime) = 0; //Update demo specific related variables
    virtual bool Destroy() = 0;               //Destroys, if necessary, variables created on init

    //Run related funtions
    void UpdateInput();
    void UpdateTime();

    IWindowManager *windowManager;
    Clock *clock;
};