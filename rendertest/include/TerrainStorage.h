#pragma once

#include <vector>
#include <unordered_map>
#include "Chunk.h"



// Explanation of chunk system can be found in Chunk.h
class TerrainStorage {
private:
    std::unordered_map<int, std::unordered_map<int, Chunk>> chunks_;

    static auto Distance(float x1, float y1, float x2, float y2);
    static auto CreateSquare(std::vector<std::array<int, 2>> &squareChunks, std::array<int, 2> centreChunk, int radius) -> void;
    static auto ConvertWorldCoordinatesToChunkCoordinates(float worldX, float worldY) -> std::array<int, 2>;
    static auto GetChunkCoordinatesInSquare(float worldX, float worldY, int radius) -> std::vector<std::array<int, 2>>;

    auto GetChunk   (int chunkX, int chunkY) -> Chunk*;
    auto GetVertices(int chunkX, int chunkY) const -> std::vector<Vertex>;

    auto AddChunk   (int chunkX, int chunkY, const Chunk &chunk) -> void;
    auto DeleteChunk(int chunkX, int chunkY) -> void;

public:
    static auto GetChunkCoordinatesInRadius(float worldX, float worldY, int radius) -> std::vector<std::array<int, 2>>;

    auto GenerateChunk          (int chunkX, int chunkY) -> void;
    auto GenerateChunksInRadius (float worldX, float worldY, int radius) -> void;
    auto ChunkExists            (int chunkX, int chunkY) const -> bool;

    auto GetAllVertices(const std::vector<std::array<int, 2>> &chunksToRender) -> std::vector<Vertex>;
};