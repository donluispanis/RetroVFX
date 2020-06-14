/*#include "FireDemo.h"

int main()
{

    FireDemo f;
    if (!f.Construct("Fire", 1280, 720, false))
        return -1;

    f.Run();
    f.Close();

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>

// Include the Emscripten library only if targetting WebAssembly
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#endif

#include <GLFW/glfw3.h>
#include <iostream>

//===============================================================
//===============================================================
//===============================================================
const float ScreenCoordinates[] = {
    -1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 1.0f};

const int VertexOrdering[] = {
    0, 1, 2,
    2, 3, 0};

const char *VertexShader =
    R"glsl(#version 300 es
    precision highp float;
    in vec2 position;
    in vec2 texcoord;
    out vec2 Texcoord;
    void main()
    {
        Texcoord = texcoord;
        gl_Position = vec4(position, 0.0, 1.0);
    }
    )glsl";

const char *FragmentShader =
    R"glsl(#version 300 es
    precision highp float;
    in vec2 Texcoord;
    out vec4 outColor;
    uniform sampler2D screenData;
    void main()
    {
        outColor = texture(screenData, Texcoord);
    }
    )glsl";
//===============================================================
//===============================================================
//===============================================================


GLFWwindow* window;

// Handle GLFW Errors
static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

// Handle key presses
static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void force_exit() {
#ifdef __EMSCRIPTEN__
  emscripten_force_exit(EXIT_FAILURE);
#else
  exit(EXIT_FAILURE);
#endif
}

unsigned char* screenPixels;

// Generate the frame data.
static void generate_frame() {
    for(int i = 0; i < 1280 * 720 * 3; i++)
    {
        screenPixels[i] = rand() % 255;
    }

  // Clear the window with the background color
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixels);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // Flip the double buffer
  glfwSwapBuffers(window);
  // Handle any events
  glfwPollEvents();
}

int main() {
  // Setup the Error handler
  glfwSetErrorCallback(error_callback);

  // Start GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Error: GLFW Initialization failed.");
    force_exit();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  // Create the display window
  window = glfwCreateWindow(1280, 720, "Demo", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error: GLFW Window Creation Failed");
    glfwTerminate();
    force_exit();
  }
  // Setup the Key Press handler
  glfwSetKeyCallback(window, key_callback);
  // Select the window as the drawing destination
  glfwMakeContextCurrent(window);


//===============================================================
//===============================================================
//===============================================================
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenCoordinates), ScreenCoordinates, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexOrdering), VertexOrdering, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShader, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShader, nullptr);
    glCompileShader(fragmentShader);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    glUseProgram(programID);

    GLint testval;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testval);
    if(testval == GL_FALSE)
    {
        char infolog[1024];
        glGetShaderInfoLog(vertexShader,1024,NULL,infolog);
        std::cout << "The vertex shader failed to compile with the error:" << std::endl << infolog << std::endl;
    }
        
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testval);
    if(testval == GL_FALSE)
    {
        char infolog[1024];
        glGetShaderInfoLog(fragmentShader,1024,NULL,infolog);
        std::cout << "The fragment shader failed to compile with the error:" << std::endl << infolog << std::endl;
    }

    glDetachShader(programID, fragmentShader);
    glDetachShader(programID, vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    GLint posAttrib = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(programID, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    screenPixels = new unsigned char[1280 * 720 * 3];

    GLuint textureID;
    glGenTextures(1, &textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, screenPixels);
    glUniform1i(glGetUniformLocation(programID, "screenData"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//===============================================================
//===============================================================
//===============================================================

  // Run the loop correctly for the target environment
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(generate_frame, 0, false);
#else
  // Display the window until ESC is pressed
  while (!glfwWindowShouldClose(window)) {
    generate_frame();
  }
  // Clean up
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
#endif
}