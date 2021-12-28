#pragma once

#include <vector>
#include <unordered_map>
#include "Chunk.h"



// Explanation of chunk system can be found in Chunk.h
class Map {
private:
    std::unordered_map<int, std::unordered_map<int, Chunk>> chunks;

    std::vector<std::vector<Vertex>> GenerateChunkVertices(const int chunkX, const int chunkZ) const;

    Chunk &GetChunk (const int x, const int z);
    void AddChunk   (const int x, const int z, const Chunk chunk);
    void DeleteChunk(const int x, const int z);

    std::vector<Vertex> GetVertices(const int x, const int z) const;

public:
    Map();

    void GenerateChunk(const int x, const int z);
    bool ChunkExists  (const int x, const int z) const;

    std::vector<Vertex> GetAllVertices(const std::vector<std::array<int, 2>> &chunksToRender);
};