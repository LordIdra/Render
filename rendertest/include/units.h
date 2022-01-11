#pragma once

#include <glm/glm.hpp>



using Color       = glm::vec4;
using WorldCoord  = glm::vec3;
using ChunkCoord  = glm::ivec2;
using ChunkCorner = glm::ivec2;
using Gradient    = glm::vec2;

enum Direction {
    north,
    east,
    northeast
};