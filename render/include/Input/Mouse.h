#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"



namespace Mouse {
    namespace Detail {
        extern const double POSITION_SENSITIVITY;
        extern const double SCROLL_SENSITIVITY;
        extern glm::vec2 positionPrevious;
        extern glm::vec2 scrollPrevious;

        void MoveCallback(GLFWwindow* window, double xpos, double ypos);
        void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    }

    extern glm::vec2 position;
    extern glm::vec2 positionDelta;
    extern glm::vec2 scrollDelta;

    void Initialize();
    void Reset();

    void Show();
    void Hide();
}