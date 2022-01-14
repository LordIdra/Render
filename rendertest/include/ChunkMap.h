#pragma once

#include "Chunk.h"
#include "util.h"
#include <unordered_map>



struct ChunkMap {
    std::unordered_map<int, std::unordered_map<int, Chunk>> map;
    auto Get(ChunkCoord coord) const -> Chunk;
    auto GetPointer(ChunkCoord coord) -> Chunk*;
    auto Set(ChunkCoord coord, const Chunk &chunk) -> void;
    auto Delete(ChunkCoord coord) -> void;
    auto Exists(ChunkCoord coord) const -> bool;
};