#pragma once

#include "Window/window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"



namespace mouse {
    auto Initialize() -> void;
    auto Update() -> void;

    auto GetPositionDelta() -> glm::vec2;
    auto GetScrollDelta() -> glm::vec2;

    auto Show() -> void;
    auto Hide() -> void;
}