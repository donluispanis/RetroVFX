#pragma once

class IWindowManager;
class Clock;

class ClassicDemoTemplate
{

  protected:
    struct Pixel;

  public:
    ClassicDemoTemplate() {}
    virtual ~ClassicDemoTemplate() {}

    //Basic use functions
    bool Construct(const char *name, const int width, const int height, const bool fullscreen); //Creates a screen using OpenGL and provides a mode of accesing pixels
    void Run();                                                                                 //Starts the application
    bool Close();                                                                               //Destroys the window and the pixel data

    //Getters
    int GetChannels() { return channels; }
    unsigned char *GetScreenData() { return screenData; }
    Pixel *GetScreenPixels() { return screenPixels; }
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
    void DrawToScreen();

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

    const int channels = 3;

    //OpenGL related variables
    union {
        unsigned char *screenData;
        Pixel *screenPixels;
    };

    unsigned int textureID;
    unsigned int programID;

    IWindowManager *windowManager;
    Clock *clock;
};