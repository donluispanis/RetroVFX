#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

#include "ClassicDemoTemplate.h"

//Window and OpenGL initialization
//Parameters: Witdh, Height
bool ClassicDemoTemplate::Construct(const char* name, const int width, const int height, const bool fullscreen)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    //Specify OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //Specify screen width and height, and app name
    this->width = width;
    this->height = height;
    this->name = name;

    //Create window
    if(fullscreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        glfwGetMonitorPhysicalSize(monitor, &this->width, &this->height);
        window = glfwCreateWindow(this->width, this->height, name, monitor, NULL);
    }
    else 
    {
        window = glfwCreateWindow(width, height, name, NULL, NULL);
    }
    
    //Stop execution if and error occurs
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return false;
    }

    //Current context, input and framerate
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize screen data and clock
    screenData = new unsigned char [this->width * this->height * 3];
    clockOld = std::chrono::system_clock::now();
    clockNow = clockOld;
    fDeltaTime = 0.f;

    //===============================================================================
    //Execute Init function defined by the user
    if(!Init())
        return false;
    //===============================================================================

    return true;
}

//Engine basic update
void ClassicDemoTemplate::Run(float framerate, float duration);
{
    while (glfwWindowShouldClose(window) == 0)
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        //Update engine time
        UpdateTime();
        /*
        //Update engine delta time count
void ClassicDemoTemplate::UpdateTime()
{
    //Extract framerate
    clockOld = clockNow;
    clockNow = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed_seconds = clockNow - clockOld;
    fDeltaTime = elapsed_seconds.count();
    timeCounter += fDeltaTime;

    if (timeCounter > 0.5f)
    {
        std::string title = "PaintLike - FPS: " + std::to_string(1 / fDeltaTime);
        glfwSetWindowTitle(window, title.c_str());
        timeCounter = 0.0f;
    }
}
        */

        //===============================================================================
        bool ret = Update(fDeltaTime);  //Update function defined by the user
        //===============================================================================
            

        // Draw
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, screenData);

        // Swap buffers
        glfwSwapBuffers(window);
    }
}

//Window and variables deletion
bool ClassicDemoTemplate::Close()
{
    //===============================================================================
    bool ret = Destroy();  //Destroy function defined by the user
    //===============================================================================

    delete[] screenData;

    glfwDestroyWindow(window);
    glfwTerminate();

    return ret;
}

