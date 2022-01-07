#include "mouse.h"

#include <iostream>



namespace mouse {
    namespace {

        glm::vec2 positionPrevious_;
        glm::vec2 position_;
        glm::vec2 positionDelta_;
        glm::vec2 scrollDelta_;

        void MoveCallback(GLFWwindow* glfwWindow, double xpos, double ypos) {
            positionPrevious_ = position_;
            position_.x = (float)xpos / (float)window::GetWidth();
            position_.y = (float)ypos / (float)window::GetHeight();
            positionDelta_ = position_ - positionPrevious_;
        }

        void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            scrollDelta_ = glm::vec2(xoffset, yoffset);
        }
    }

    auto Initialize() -> void {
        glfwSetCursorPosCallback(window::GetWindow(), MoveCallback);
        glfwSetScrollCallback(window::GetWindow(), ScrollCallback);
    }

    void Update() {
        positionDelta_ = glm::vec2(0);
        scrollDelta_ = glm::vec2(0);
    }

    auto GetPositionDelta() -> glm::vec2 {
        return positionDelta_;
    }

    auto GetScrollDelta() -> glm::vec2 {
        return scrollDelta_;
    }

    void Show() {
        glfwSetInputMode(window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Hide() {
        glfwSetInputMode(window::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    }
}