#include "Input/Mouse.h"

#include "Window/Window.h"
#include <iostream>



namespace Mouse {
    namespace Detail {
        const double POSITION_SENSITIVITY = 10.0;
        const double SCROLL_SENSITIVITY = 1.0;

        glm::vec2 positionPrevious;

        void MoveCallback(GLFWwindow* window, double xpos, double ypos) {
            positionPrevious = position;
            position.x = (xpos * POSITION_SENSITIVITY) / Window::Detail::width;
            position.y = (ypos * POSITION_SENSITIVITY) / Window::Detail::height;
            positionDelta = position - positionPrevious;
        }

        void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            scrollDelta = glm::vec2(xoffset, yoffset);
        }
    }

    glm::vec2 position;
    glm::vec2 positionDelta;
    glm::vec2 scrollDelta;

    void Initialize() {
        glfwSetCursorPosCallback(Window::GetWindow(), Detail::MoveCallback);
        glfwSetScrollCallback(Window::GetWindow(), Detail::ScrollCallback);
    }

    void Reset() {
        positionDelta = glm::vec2(0);
        scrollDelta = glm::vec2(0);
    }

    void Show() {
        glfwSetInputMode(Window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Hide() {
        glfwSetInputMode(Window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    }
}