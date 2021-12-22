#pragma once

#include <../include/glad/glad.h>
#include <../include/GLFW/glfw3.h>


namespace Mouse {
    namespace {
        GLFWwindow *window;
        double x;
        double y;
        double prevx;
        double prevy;
    }

    void SetWindow(GLFWwindow *const window);
    void Update();
    void Show();
    void Hide();
}