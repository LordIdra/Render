#pragma once

#include <algorithm>
#include <glm/glm.hpp>
#include <unordered_map>



using Color       = glm::vec4;
using WorldCoord  = glm::vec3;
using ChunkCoord  = glm::ivec2;
using ChunkCorner = glm::ivec2;
using Gradient    = glm::vec2;

enum Direction {
    north,
    northeast,
    east,
    southeast,
    south,
    southwest,
    west,
    northwest
};

template<typename AT, typename ET>
auto Contains(AT array, ET target) -> bool {;
    return (std::find(array.begin(), array.end(), target) != array.end());
}