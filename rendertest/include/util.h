#pragma once

#include <algorithm>
#include <glm/glm.hpp>
#include <unordered_map>



using Color       = glm::vec4;      // color
using WorldCoord  = glm::vec3;      // can represent any point in 3D space on the map
using PlaneCoord  = glm::vec2;      // can represent any point on the X and Z components of the map
using ChunkCoord  = glm::ivec2;     // can represent any chunm on the map
using ChunkCorner = glm::ivec2;     // represents the position of a chunk corner
using Gradient    = glm::vec2;      // gradient vector used in noise generation

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