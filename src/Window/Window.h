#pragma once

#include <../include/glad/glad.h>
#include <../include/GLFW/glfw3.h>
#include <string>



namespace Window {

    namespace Detail {
        const int SAMPLES = 4;
        const std::string NAME = "Test";
        const int MAJOR_VERSION = 3;
        const int MINOR_VERSION = 3;

        extern GLFWmonitor *monitor;
        extern GLFWwindow *window;
        extern const GLFWvidmode *mode;

        extern int width;
        extern int height;
        extern int deltaTime;

        void SetVersionHints();
        void AcquireMonitor();

        void SetColorHints();
        void SetRenderHints();

        void CreateWindow();
        void AcquireWindowParameters();

        void InitializeGlfw();
        void InitializeGlad();
        void InitializeHints();
        void InitializeWindow();
    }

    void Initialize();
    void Clear();
    void Background(const float r, const float g, const float b, const float a);
    void SwapBuffers();
    void PollEvents();
    void UpdateTime();
    void UpdateMouse();

    bool ShouldClose();
    void SetShouldClose();

    void Terminate();
}
