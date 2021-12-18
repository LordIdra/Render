#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Mouse {
    namespace {
        GLFWwindow *window;
        double x;
        double y;
        double prevx;
        double prevy;
    }

    void SetWindow(GLFWwindow *window);
    void Update();
    void Show();
    void Hide();
}