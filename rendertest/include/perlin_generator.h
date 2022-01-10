#pragma once

#include <vector>



namespace perlin_generator {
    auto Initialize(int seed) -> void;
    auto GenerateNumberSet(int size, int range, int precision) -> std::vector<float>;
}