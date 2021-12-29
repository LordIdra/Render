#include "Input/Keys.h"

#include "Window/Window.h"



namespace Keys {
    namespace Detail {
        std::unordered_map<unsigned int, void(*)()> functionCalledWhenKeyPressed;
        std::unordered_map<unsigned int, void(*)()> functionCalledWhenKeyReleased;
        
        void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            switch (action) {
            case GLFW_PRESS:
                if (ElementExists(Detail::functionCalledWhenKeyPressed, key)) {
                    Detail::functionCalledWhenKeyPressed.at(key)();
                }
                break;

            case GLFW_RELEASE:
                if (ElementExists(Detail::functionCalledWhenKeyReleased, key)) {
                    Detail::functionCalledWhenKeyReleased.at(key)();
                }
                break;
            }
        }

        bool ElementExists(std::unordered_map<unsigned int, void(*)()> map, unsigned int key) {
            return (map.find(key) != map.end());
        }
    }

    void Initialize() {
        glfwSetKeyCallback(Window::GetWindow(), Detail::KeyEventCallback);
    }

    bool KeyHeldDown(unsigned int key) {
        return (glfwGetKey(Window::GetWindow(), key) == GLFW_PRESS);
    }

    void BindFunctionToKeyPress(const unsigned int key, void (*function)()) {
        Detail::functionCalledWhenKeyPressed[key] = function;
    }

    void BindFunctionToKeyRelease(const unsigned int key, void (*function)()) {
        Detail::functionCalledWhenKeyReleased[key] = function;
    }
}