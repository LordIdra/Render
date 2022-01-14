#include "ChunkMap.h"
#include "util.h"
#include <iostream>




auto ChunkMap::Get(ChunkCoord coord) const -> Chunk {
    return map.at(coord.x).at(coord.y);
}

auto ChunkMap::GetPointer(ChunkCoord coord) -> Chunk* {
    return &(map.at(coord.x).at(coord.y));
}

auto ChunkMap::Set(ChunkCoord coord, const Chunk &chunk) -> void {
    map[coord.x][coord.y] = chunk;
}

auto ChunkMap::Delete(ChunkCoord coord) -> void {
    map[coord.x].erase(coord.y);
}

auto ChunkMap::Exists(ChunkCoord coord) const -> bool {
    if (map.find(coord.x) == map.end()) { return false; }
    return (map.at(coord.x).find(coord.y)) != map.at(coord.x).end(); 
   
}