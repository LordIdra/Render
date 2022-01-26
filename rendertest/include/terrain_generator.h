#pragma once

#include "util.h"
#include <vector>



namespace terrain_generator {
    auto Initialize(unsigned int seed) -> void;
    auto GetHeight(ChunkCoord chunkCoord, PlaneCoord planeCoord) -> float;
}