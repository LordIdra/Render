#pragma once

#include <glm/glm.hpp>



using Color       = glm::vec4;
using WorldCoord2 = glm::vec2;
using WorldCoord  = glm::vec3;
using ChunkCoord  = glm::ivec2;
using ChunkCorner = glm::ivec2;
using Gradient    = glm::vec2;

struct CornerSet {
    ChunkCorner north;
    ChunkCorner east;
    ChunkCorner south;
    ChunkCorner west;
};

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