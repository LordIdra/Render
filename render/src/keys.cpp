#include "keys.h"
#include "window.h"



namespace keys {
    namespace {
        std::unordered_map<unsigned int, void(*)()> functionCalledWhenKeyPressed_; 
        std::unordered_map<unsigned int, void(*)()> functionCalledWhenKeyReleased_;                                                          
        auto ElementExists(std::unordered_map<unsigned int, void(*)()> map, unsigned int key) -> bool{
            return (map.find(key) != map.end());
        }
        
        auto KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {    //NOLINT - function must be in this format to work with glfwSetKeyCallback
            switch (action) {
            case GLFW_PRESS:
                if (ElementExists(functionCalledWhenKeyPressed_, key)) {
                    functionCalledWhenKeyPressed_.at(key)();
                }
                break;

            case GLFW_RELEASE:
                if (ElementExists(functionCalledWhenKeyReleased_, key)) {
                    functionCalledWhenKeyReleased_.at(key)();
                }
                break;
            }
        }
    }

    auto Initialize() -> void {
        glfwSetKeyCallback(window::GetWindow(), KeyEventCallback);
    }

    auto BindFunctionToKeyPress(const int key, void (*function)()) -> void {
        functionCalledWhenKeyPressed_[key] = function;
    }
    
    auto BindFunctionToKeyRelease(const int key, void (*function)()) -> void {
        functionCalledWhenKeyReleased_[key] = function;
    }

    auto KeyHeldDown(int key) -> bool {
        return (glfwGetKey(window::GetWindow(), key) == GLFW_PRESS);
    }
}