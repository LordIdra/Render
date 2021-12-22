#pragma once

#include <../include/glad/glad.h>
#include <../include/GLFW/glfw3.h>


namespace Keys {
    namespace {
        GLFWwindow *window;
    }

    void SetWindow(GLFWwindow *const window);
    bool KeyDown(const unsigned int key);
}