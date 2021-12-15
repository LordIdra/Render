#include "Mouse.h"


void Mouse::SetWindow(GLFWwindow* window) {
    Mouse::window = window;
}

void Mouse::Update() {
    prevx = x;
    prevy = y;
    glfwGetCursorPos(window, &x, &y);
}

void Mouse::Show() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Mouse::Hide() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
}