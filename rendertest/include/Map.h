#pragma once

#include <vector>
#include <unordered_map>
#include "Chunk.h"



enum Direction {
    north,
    east,
    northeast
};



// Explanation of chunk system can be found in Chunk.h
class Map {
private:
    std::unordered_map<int, std::unordered_map<int, Chunk>> chunks;

    std::vector<std::vector<Vertex>> GenerateChunkVertices(const int chunkX, const int chunkZ) const;

    bool ChunkExists(const int x, const int z) const;
    Chunk &GetChunk(const int x, const int z);
    void AddChunk(const int x, const int z, const Chunk chunk);
    void DeleteChunk(const int x, const int z);

    std::vector<Vertex> GetVertices(int x, int z);

    void AddFirstTriangles(std::vector<unsigned int> &indices, const int jConstant) const;
    void AddSecondTriangles(std::vector<unsigned int> &indices, const int jConstant) const;

    std::array<int, 2> GetRelativeCoords(Direction direction, std::array<int, 2> coords);

    void JoinAdjacentChunks(
       std::vector<unsigned int> &indices, 
       const std::vector<std::array<int, 2>> &chunksToRender, 
       const std::array<int, 2> coords, 
       const int chunkConstant);

public:
    Map();

    void GenerateChunk(const int x, const int z);

    std::vector<Vertex> GetAllVertices(const std::vector<std::array<int, 2>> &chunksToRender);
    std::vector<unsigned int> GetAllIndices(std::vector<std::array<int, 2>> &chunksToRender);
};