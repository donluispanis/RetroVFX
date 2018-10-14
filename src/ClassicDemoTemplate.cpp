#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "ClassicDemoTemplate.h"

//Window, Engine and OpenGL initialization
bool ClassicDemoTemplate::Construct(const char *name, const int width, const int height, const bool fullscreen)
{
    if (!glfwInit())
        return ShowError("Failed to initialize GLFW");

    SetOpenGLVersion();
    SetWindowName(name);

    if (fullscreen)
        CreateFullscrenWindow();
    else
        CreateWindow(width, height);

    if (window == NULL)
        return ShowError("Failed to open GLFW window");

    AddGLFWOptions();

    /******************************************************************************************************/

    // Shader sources
    const GLchar *vertexSource = R"glsl(
    #version 450 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main()
    {
        Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
    const GLchar *fragmentSource = R"glsl(
    #version 450 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        outColor = vec4(Color, 1.0);
    }
)glsl";

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


    /******************************************************************************************************/
    InitEngineData();

    if (!Init())
        return ShowError("Failed to execute user defined Init function");

    return true;
}

#pragma region [CONSTRUCT PRIVATE FUNCTIONS]

void ClassicDemoTemplate::SetOpenGLVersion()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

void ClassicDemoTemplate::SetWindowName(const char *name)
{
    this->name = name;
}

void ClassicDemoTemplate::CreateFullscrenWindow()
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPhysicalSize(monitor, &this->width, &this->height);
    window = glfwCreateWindow(this->width, this->height, name, monitor, NULL);
}

void ClassicDemoTemplate::CreateWindow(const int width, const int height)
{
    this->width = width;
    this->height = height;

    window = glfwCreateWindow(width, height, name, NULL, NULL);
}

void ClassicDemoTemplate::AddGLFWOptions()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void ClassicDemoTemplate::InitEngineData()
{
    screenData = new unsigned char[this->width * this->height * 3];

    clockOld = std::chrono::system_clock::now();
    clockNow = clockOld;
    fDeltaTime = 0.f;
}

bool ClassicDemoTemplate::ShowError(const char *message)
{
    std::cerr << message << std::endl;
    glfwTerminate();
    return false;
}

#pragma endregion

//Engine basic update
void ClassicDemoTemplate::Run(float duration)
{
    while (glfwWindowShouldClose(window) == 0 && duration > 0)
    {
        SetScreenBlack();
        UpdateInput();
        UpdateTime();

        if (!Update(fDeltaTime))
            return; //Update function defined by the user

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        DrawToScreen();

        duration -= fDeltaTime;
    }
}

#pragma region [RUN PRIVATE FUNCTIONS]

void ClassicDemoTemplate::SetScreenBlack()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClassicDemoTemplate::UpdateInput()
{
    glfwPollEvents();

    int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void ClassicDemoTemplate::UpdateTime()
{
    clockOld = clockNow;
    clockNow = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed_seconds = clockNow - clockOld;
    fDeltaTime = elapsed_seconds.count();
}

void ClassicDemoTemplate::DrawToScreen()
{
    glfwSwapBuffers(window);
}

#pragma endregion

//Window and variables deletion
bool ClassicDemoTemplate::Close()
{
    bool ret = Destroy(); //Destroy function defined by the user

    delete[] screenData;

    glfwDestroyWindow(window);
    glfwTerminate();

    return ret;
}
