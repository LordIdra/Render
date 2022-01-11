#pragma once

#include "units.h"
#include <vector>



namespace terrain_generator {
    auto Initialize(unsigned int seed) -> void;
    auto GenerateNumberSet(int size, int range, int precision) -> std::vector<float>;

    auto GenerateRandomGradient() -> glm::vec2;
    auto GetGradient(ChunkCorner corner) -> float;
}