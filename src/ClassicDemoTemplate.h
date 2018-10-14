#pragma once

#include <chrono>
#include <GL/gl.h>

class GLFWwindow;

class ClassicDemoTemplate
{
public:
  ClassicDemoTemplate() {}
  virtual ~ClassicDemoTemplate() {}

  //Basic use functions
  bool Construct(const char *name, const int width, const int height, const bool fullscreen); //Creates a screen using OpenGL and provides a mode of accesing pixels
  void Run(float duration);                                                                   //Causes the demo to run for the given time
  bool Close();                                                                               //Destroys the window and the pixel data

  //Getters
  int GetWidth() { return width; }
  int GetHeight() { return height; }
  unsigned char *GetScreenData() { return screenData; }

private:
  //Functions that have to be overwritten by the implementation
  virtual bool Init() = 0;                   //Init demo specific related variables
  virtual bool Update(float fDeltaTime) = 0; //Update demo specific related variables
  virtual bool Destroy() = 0;                //Destroys, if necessary, variables created on init

  //Run related funtions
  void SetScreenBlack();
  void UpdateInput();
  void UpdateTime();
  void DrawToScreen();

  //Init related functions
  void SetOpenGLVersion();
  void SetWindowName(const char *name);
  void CreateFullscrenWindow();
  void CreateWindow(const int width, const int height);
  void AddGLFWOptions();
  void InitEngineData();
  bool ShowError(const char *message);

  //Window related variables
  int height;
  int width;
  const char *name;
  GLFWwindow *window;
  unsigned char *screenData;

  //Time related variables
  std::chrono::system_clock::time_point clockOld;
  std::chrono::system_clock::time_point clockNow;
  float fDeltaTime;
};