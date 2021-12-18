#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Keys {
    namespace {
        GLFWwindow *window;
    }

    void SetWindow(GLFWwindow *window);
    bool KeyDown(unsigned int key);
}