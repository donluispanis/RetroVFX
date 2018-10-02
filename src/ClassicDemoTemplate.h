#pragma once

#include <chrono>
#include <vector>

class Tool;
class Canvas;
class GLFWwindow;

class ClassicDemoTemplate
{

  public:

    //Void Constructor and Destructor
    ClassicDemoTemplate() {}
    virtual ~ClassicDemoTemplate() {}

    //Functions to use the template
    bool Construct(const char* name, const int width, const int height, const bool fullscreen); //Creates a screen using OpenGL and provides a mode of accesing pixels
    bool Run(float framerate, float duration); //Causes the game to run at a given framrated for a limited time. If set to 0, the framerate and duration are unlimited
    bool Close(); //Destroys the windows and the pixel data 

    //Getters
    int GetWidth()  {   return width; }
    int GetHeight() {   return height;}
    unsigned char* GetScreenData() {  return screenData;}

  private:
    //===============================================================================
    // PRIVATE FUNCTIONS
    //===============================================================================

    //Functions that have to be overwritten by the implementation
    virtual bool Init() = 0;  //Init demo specific related variables
    virtual bool Update(float fDeltaTime) = 0;  //Update demo specific related variables
    virtual bool Destroy() = 0;  //Destroys, if necessary, variables created on init

    //===============================================================================
    // WINDOW RELATED VARIABLES
    //===============================================================================

    int height;
    int width;
    GLFWwindow *window;
    unsigned char *screenData;
    const char* name;

    //===============================================================================
    // TIME RELATED VARIABLES
    //===============================================================================

    std::chrono::system_clock::time_point clockOld;
    std::chrono::system_clock::time_point clockNow;
    float fDeltaTime;

};