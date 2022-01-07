#pragma once

#include <string>



namespace init {
    auto Initialize(const std::string &windowName) -> void;
    auto Terminate() -> void;
}