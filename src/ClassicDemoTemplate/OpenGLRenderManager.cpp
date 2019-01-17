#include "OpenGLRenderManager.h"
#include "Pixel.h"

#include <GL/glew.h>
#include <GL/gl.h>

void OpenGLRenderManager::InitialiseRender(int width, int height)
{
    this->width = width;
    this->height = height;
    screenPixels = (Pixel*)new unsigned char[width * height * channels];

    InitGlew();
    InitOpenGL();
}

void OpenGLRenderManager::InitGlew()
{
    glewExperimental = GL_TRUE;
    glewInit();
}

void OpenGLRenderManager::InitOpenGL()
{
    CreateVAOandVBO();
    CreateElementBuffers();
    CreateOpenGLProgram();
    SetShaderVariables();
    SetTexture();
}

void OpenGLRenderManager::CreateVAOandVBO()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {//Every corner of the window
                          //Position | Texcoords
                          -1.0f, 1.0f, 0.0f, 0.0f,
                          1.0f, 1.0f, 1.0f, 0.0f,
                          1.0f, -1.0f, 1.0f, 1.0f,
                          -1.0f, -1.0f, 0.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void OpenGLRenderManager::CreateElementBuffers()
{
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

void OpenGLRenderManager::CreateOpenGLProgram()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vs = GetVertexShader();
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs = GetFragmentShader();
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glBindFragDataLocation(programID, 0, "outColor");
    glLinkProgram(programID);
    glUseProgram(programID);

    glDetachShader(programID, fragmentShader);
    glDetachShader(programID, vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}

const char *OpenGLRenderManager::GetVertexShader()
{
    return
        R"glsl(
    #version 150 core
    in vec2 position;
    in vec2 texcoord;
    out vec2 Texcoord;
    void main()
    {
        Texcoord = texcoord;
        gl_Position = vec4(position, 0.0, 1.0);
    }
    )glsl";
}

const char *OpenGLRenderManager::GetFragmentShader()
{
    return
        R"glsl(
    #version 150 core
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D screenData;
    void main()
    {
        outColor = texture(screenData, Texcoord);
    }
    )glsl";
}

void OpenGLRenderManager::SetShaderVariables()
{
    GLint posAttrib = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(programID, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
}

void OpenGLRenderManager::SetTexture()
{
    glGenTextures(1, &textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixels);
    glUniform1i(glGetUniformLocation(programID, "screenData"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OpenGLRenderManager::DisposeRender()
{
    delete[] screenPixels;
}

OpenGLRenderManager::~OpenGLRenderManager()
{
}

Pixel *OpenGLRenderManager::GetScreenPixels()
{
    return screenPixels;
}

void OpenGLRenderManager::DrawToScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixels);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}