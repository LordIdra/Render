#pragma once

#include "units.h"
#include <vector>



namespace terrain_generator {
    auto Initialize(unsigned int seed) -> void;
    auto GetHeight(ChunkCoord chunkCoord, WorldCoord worldCoord);
}