#pragma once

#include <unordered_map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "window.h"



namespace keys {
    auto Initialize() -> void;
    auto BindFunctionToKeyPress(int key, void (*function)()) -> void;
    auto BindFunctionToKeyRelease(int key, void (*function)()) -> void;
    auto KeyHeldDown(int key) -> bool;
}