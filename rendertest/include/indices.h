#pragma once

#include <vector>
#include <array>
#include "TerrainStorage.h"



namespace indices {

    enum Direction {
        north,
        east,
        northeast
    };

    template<typename AT, typename ET>
    auto Contains(AT array, ET target) -> bool;

    auto AddFirstMainTriangles              (std::vector<unsigned int> &indices, int j) -> void;
    auto AddSecondMainTriangles             (std::vector<unsigned int> &indices, int j) -> void;
    auto AddFirstNorthTriangles             (std::vector<unsigned int> &indices, int adjacentConstant, int chunkConstant, int i) -> void;
    auto AddSecondNorthTriangles            (std::vector<unsigned int> &indices, int adjacentConstant, int chunkConstant, int i) -> void;
    auto AddEastTriangles                   (std::vector<unsigned int> &indices, int adjacentConstant, int chunkConstant, int i) -> void;
    auto AddNorthEastTrianglesFacingNorth   (std::vector<unsigned int> &indices, int adjacentConstant, int diagonalConstant, int chunkConstant) -> void;
    auto AddNorthEastTrianglesFacingEast    (std::vector<unsigned int> &indices, int adjacentConstant, int diagonalConstant, int chunkConstant) -> void;

    auto GetRelativeCoords(Direction direction, std::array<int, 2> coords) -> std::array<int, 2>;
    auto GetIndex(const std::vector<std::array<int, 2>> &chunksToRender, std::array<int, 2> coords) -> int;

    auto DrawNorthTriangles               (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                           std::array<int, 2> coords, int chunkConstant) -> void;
    auto DrawEastTriangles                (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                           std::array<int, 2> coords, int chunkConstant) -> void;
    auto DrawNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                           std::array<int, 2> coords, int chunkConstant) -> void;
    auto DrawNorthEastTrianglesFacingEast (std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                           std::array<int, 2> coords, int chunkConstant) -> void;

    auto DrawNorthEastTriangles(const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                                const std::vector<std::array<int, 2>> &chunksToRender, std::array<int, 2> coords, int chunkConstant) -> void;
    auto JoinAdjacentChunks    (const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                                const std::vector<std::array<int, 2>> &chunksToRender, std::array<int, 2> coords, int chunkConstant) -> void;

    auto GetChunkIndices(std::vector<unsigned int> &indices, unsigned int chunkConstant) -> void;

    auto GetAllIndices(const TerrainStorage *terrainStorage, const std::vector<std::array<int, 2>> &chunksToRender) -> std::vector<unsigned int>;
}