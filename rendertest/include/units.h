#pragma once

#include <glm/glm.hpp>



using Color      = glm::vec4;
using WorldCoord = glm::vec3;
using ChunkCoord = glm::ivec2;

enum Direction {
    north,
    east,
    northeast
};