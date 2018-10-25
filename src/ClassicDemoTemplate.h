#pragma once

#include <chrono>

class GLFWwindow;

class ClassicDemoTemplate
{

protected:
  struct Pixel
  {
    unsigned char R = 0;
    unsigned char G = 0;
    unsigned char B = 0;

    Pixel() : R(0), G(0), B(0){};
    Pixel(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b){};
    Pixel operator+(const Pixel &p) const;
    Pixel operator-(const Pixel &p) const;
    Pixel operator*(const float f) const;
    void Clear()
    {
      R = 0;
      G = 0;
      B = 0;
    }
  };

public:
  ClassicDemoTemplate() {}
  virtual ~ClassicDemoTemplate() {}

  //Basic use functions
  bool Construct(const char *name, const int width, const int height, const bool fullscreen); //Creates a screen using OpenGL and provides a mode of accesing pixels
  void Run();                                                                                 //Starts the application
  bool Close();                                                                               //Destroys the window and the pixel data

  //Getters
  int GetWidth() { return width; }
  int GetHeight() { return height; }
  int GetChannels() { return channels; }
  unsigned char *GetScreenData() { return screenData; }
  Pixel *GetScreenPixels() { return screenPixels; }
  float GetElapsedTime() { return elapsedTime; }

  //Setters
  void ShowFPS(bool fps) { showFramerate = fps; }
  bool ShowError(const char *message);

private:
  //Functions that have to be overwritten by the implementation
  virtual bool Init() = 0;                  //Init demo specific related variables
  virtual bool Update(float deltaTime) = 0; //Update demo specific related variables
  virtual bool Destroy() = 0;               //Destroys, if necessary, variables created on init

  //Run related funtions
  void UpdateInput();
  void UpdateTime();
  void DrawToScreen();
  void ShowFramerate();

  //Init related functions
  void SetWindowName(const char *name);
  void CreateFullscrenWindow();
  void CreateWindow(const int width, const int height);
  void AddGLFWOptions();
  void InitEngineData();

  //OpenGL related functions
  void SetOpenGLVersion();
  void InitOpenGL();
  const char *GetVertexShader();
  const char *GetFragmentShader();
  void InitGlew();
  void CreateVAOandVBO();
  void CreateElementBuffers();
  void CreateOpenGLProgram();
  void SetShaderVariables();
  void SetTexture();

  //Window related variables
  int height;
  int width;
  const int channels = 3;
  const char *name;
  GLFWwindow *window;
  bool showFramerate = true;
  float elapsedTime = 0;

  //OpenGL related variables
  union {
    unsigned char *screenData;
    Pixel *screenPixels;
  };

  unsigned int textureID;
  unsigned int programID;

  //Time related variables
  std::chrono::system_clock::time_point clockOld;
  std::chrono::system_clock::time_point clockNow;
  float deltaTime;
};