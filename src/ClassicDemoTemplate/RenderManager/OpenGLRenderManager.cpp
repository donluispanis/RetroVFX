#include <GL/glew.h>
#include <GL/gl.h>
#include "OpenGLRenderManager.h"
#include "OpenGLValues.h"
#include "../../Utils/Pixel.h"

void OpenGLRenderManager::InitialiseRender(int width, int height)
{
    this->width = width;
    this->height = height;
    screenPixels = (Pixel *)new unsigned char[width * height * channels];

    InitGlew();
    InitOpenGL();
}

void OpenGLRenderManager::DisposeRender()
{
    delete[] screenPixels;
}

void OpenGLRenderManager::InitGlew()
{
    glewExperimental = GL_TRUE;
    glewInit();
}

void OpenGLRenderManager::InitOpenGL()
{
    CreateVAO();
    CreateVBO();
    CreateElementBuffers();
    CreateOpenGLProgram();
    SetShaderVariables();
    SetTexture();
}

void OpenGLRenderManager::CreateVAO()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void OpenGLRenderManager::CreateVBO()
{
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenCoordinates), ScreenCoordinates, GL_STATIC_DRAW);
}

void OpenGLRenderManager::CreateElementBuffers()
{
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexOrdering), VertexOrdering, GL_STATIC_DRAW);
}

void OpenGLRenderManager::CreateOpenGLProgram()
{
    GLuint vertexShader = CompileVertexShader();
    GLuint fragmentShader = CompileFragmentShader();

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glBindFragDataLocation(programID, 0, "outColor");
    glLinkProgram(programID);
    glUseProgram(programID);

    DeleteShaders(programID, vertexShader, fragmentShader);
}

int OpenGLRenderManager::CompileVertexShader()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShader, nullptr);
    glCompileShader(vertexShader);
    return vertexShader;
}

int OpenGLRenderManager::CompileFragmentShader()
{
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShader, nullptr);
    glCompileShader(fragmentShader);
    return fragmentShader;
}

void OpenGLRenderManager::DeleteShaders(int programID, int vertexShader, int fragmentShader)
{
    glDetachShader(programID, fragmentShader);
    glDetachShader(programID, vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
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

OpenGLRenderManager::~OpenGLRenderManager()
{
}

Pixel *OpenGLRenderManager::GetScreenPixels()
{
    return screenPixels;
}

void OpenGLRenderManager::DrawToScreen()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixels);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}