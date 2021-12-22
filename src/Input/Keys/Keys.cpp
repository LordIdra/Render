#include "Keys.h"


void Keys::SetWindow(GLFWwindow *const window) {
    Keys::window = window;
}

bool Keys::KeyDown(const unsigned int key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}
