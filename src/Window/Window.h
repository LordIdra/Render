#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Logging/Logging.h"
#include "../Input/Mouse/Mouse.h"
#include "../Input/Keys/Keys.h"

using namespace std;



namespace Window {

    namespace Detail {
        extern const int SAMPLES;
        extern const char* NAME;
        extern const int MAJOR_VERSION;
        extern const int MINOR_VERSION;

        extern GLFWmonitor* monitor;
        extern GLFWwindow* window;
        extern const GLFWvidmode* mode;

        extern int width;
        extern int height;
        extern int deltaTime;

        void InitializeGlfw();
        void InitializeGlad();
        void InitializeHints();
        void InitializeWindow();
    }

    void Initialize();
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
