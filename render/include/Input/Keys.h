#pragma once

#include <unordered_map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"



namespace Keys {
    namespace Detail {
        extern std::unordered_map<unsigned int, void(*)()> functionCalledWhenKeyPressed;

        bool ElementExists(std::unordered_map<unsigned int, void(*)()> map, unsigned int key);
        void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    }

    void Initialize();
    bool KeyHeldDown(const unsigned int key);
    void BindFunctionToKeyPress(const unsigned int key, void (*function)());
    void BindFunctionToKeyRelease(const unsigned int key, void (*function)());
}