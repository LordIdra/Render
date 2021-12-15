#pragma once

#include <GLFW/glfw3.h>


namespace Keys {
    namespace {
        GLFWwindow* window;
    }

    void SetWindow(GLFWwindow* window);
    bool KeyDown(const unsigned int key);
}