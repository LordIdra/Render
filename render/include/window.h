#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>



auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;

namespace window {
    void Initialize(const std::string &name);

    auto GetWindow() -> GLFWwindow*;
    [[nodiscard]] auto GetWidth() -> int;
    [[nodiscard]] auto GetHeight() -> int;

    auto Update() -> void;
    auto ShouldClose() -> bool;
    auto SetShouldClose() -> void;
};
