#pragma once

#include <vector>
#include <unordered_map>
#include "Chunk.h"
#include "ChunkMap.h"
#include "util.h"



// Explanation of chunk system can be found in Chunk.h
class TerrainStorage {
private:
    ChunkMap chunks_;

    static auto Distance(float x1, float y1, float x2, float y2);
    static auto CreateSquare(std::vector<ChunkCoord> &squareChunks, ChunkCoord centreChunk, int radius) -> void;
    static auto ConvertWorldCoordinatesToChunkCoordinates(WorldCoord coord) -> ChunkCoord;
    static auto GetChunkCoordinatesInSquare(WorldCoord coord, int radius) -> std::vector<ChunkCoord>;

    auto GetChunk   (ChunkCoord coord) -> Chunk*;
    auto GetVertices(ChunkCoord coord) const -> std::vector<Vertex>;

    auto AddChunk   (ChunkCoord coord, const Chunk &chunk) -> void;
    auto DeleteChunk(ChunkCoord coord) -> void;

public:
    static auto GetChunkCoordinatesInRadius(WorldCoord coord, int radius) -> std::vector<ChunkCoord>;

    auto GenerateChunk          (ChunkCoord coord) -> void;
    auto GenerateChunksInRadius (WorldCoord coord, int radius) -> void;
    auto ChunkExists            (ChunkCoord coord) const -> bool;

    auto GetAllVertices(const std::vector<ChunkCoord> &chunksToRender) -> std::vector<Vertex>;
};