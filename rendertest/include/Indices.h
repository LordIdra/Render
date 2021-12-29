#pragma once

#include <vector>
#include <array>
#include "TerrainStorage.h"



namespace Indices {
    enum Direction {
        north,
        east,
        northeast
    };

    void AddFirstMainTriangles              (std::vector<unsigned int> &indices, const int j);
    void AddSecondMainTriangles             (std::vector<unsigned int> &indices, const int j);
    void AddFirstNorthTriangles             (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i);
    void AddSecondNorthTriangles            (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i);
    void AddEastTriangles                   (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i);
    void AddNorthEastTrianglesFacingNorth   (std::vector<unsigned int> &indices, const int adjacentConstant, const int diagonalConstant, const int chunkConstant);
    void AddNorthEastTrianglesFacingEast    (std::vector<unsigned int> &indices, const int adjacentConstant, const int diagonalConstant, const int chunkConstant);

    std::array<int, 2> GetRelativeCoords(const Direction direction, std::array<int, 2> coords);
    auto GetIndex(const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords);

    void DrawNorthTriangles                     (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);
    void DrawEastTriangles                      (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);

    void DrawNorthEastTrianglesFacingNorth      (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);
    void DrawNorthEastTrianglesFacingEast       (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);
    void DrawNorthEastTriangles (const TerrainStorage &terrainStorage, std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);

    void JoinAdjacentChunks(const TerrainStorage &terrainStorage, std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant);
    void GetChunkIndices(std::vector<unsigned int> &indices, unsigned int chunkConstant);

    std::vector<unsigned int> GetAllIndices(const TerrainStorage& terrainStorage, const std::vector<std::array<int, 2>> &chunksToRender);
}