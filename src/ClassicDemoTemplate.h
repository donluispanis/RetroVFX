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
    ClassicDemoTemplate(const int w, const int h);
    ~ClassicDemoTemplate();

    //Basic functions
    virtual void Init() = 0;
    virtual void Update() = 0;

  private:
    //===============================================================================
    // PRIVATE FUNCTIONS
    //===============================================================================
    void Draw();              //Default draw
    void DrawAllCanvas();     //Draws all the canvases onto the screen
    void DrawTopCanvas();     //Redraws top canvas
    void DrawPartialCanvas(const int x1, const int y1, const int x2, const int y2); //Redraws canvas partially
    void DrawInterface();     //Draws interface

    bool InitWindow(const int w, const int h); //Init window and openGL related stuff
    bool InitEngine(const int w, const int h); //Init all paint related stuff

    void UpdateTime();  //Update engine delta time count
    void UpdateInput(); //Update engine input

    //===============================================================================
    // WINDOW RELATED VARIABLES
    //===============================================================================

    int height;
    int width;
    GLFWwindow *window;
    unsigned char *screenData;

    //===============================================================================
    // TIME RELATED VARIABLES
    //===============================================================================

    std::chrono::system_clock::time_point clockOld;
    std::chrono::system_clock::time_point clockNow;
    float fDeltaTime;

    float timeCounter;
};