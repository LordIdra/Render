#include "Input/Keys.h"

#include "Window/Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"




bool Keys::KeyDown(unsigned int key) {
    return (glfwGetKey(Window::GetWindow(), key) == GLFW_PRESS);
}
