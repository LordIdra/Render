#include "Keys.h"



void Keys::SetWindow(GLFWwindow *window) {
    Keys::window = window;
}

bool Keys::KeyDown(unsigned int key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}
