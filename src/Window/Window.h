#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Logging/Logging.h"
#include "../Input/Mouse/Mouse.h"
#include "../Input/Keys/Keys.h"

using namespace std;


namespace Window {
    namespace Detail {
        const int SAMPLES = 4;
        const char* NAME = "Test";
        const int MAJOR_VERSION = 3;
        const int MINOR_VERSION = 3;

        GLFWmonitor* monitor;
        GLFWwindow* window;
        const GLFWvidmode* mode;

        int width;
        int height;
        int deltaTime;
    }

    void InitializeGlfw();
    void InitializeGlad();
    void InitializeHints();
    void InitializeWindow();

    void Clear();
    void Background(float r, float g, float b, float a);
    void SwapBuffers();
    void PollEvents();
    void UpdateTime();
    void UpdateMouse();

    bool ShouldClose();
    void SetShouldClose();

    void Terminate();
}
