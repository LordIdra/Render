#include "Indices.h"

#include <algorithm>
#include "Chunk.h"



namespace Indices {
    void AddFirstMainTriangles(std::vector<unsigned int> &indices, const int j) {
        indices.push_back(j +                       0);
        indices.push_back(j +                       1);
        indices.push_back(j + Chunk::CHUNK_SIZE   + 0);

        indices.push_back(j +                       1);
        indices.push_back(j + Chunk::CHUNK_SIZE   + 0);
        indices.push_back(j + Chunk::CHUNK_SIZE   + 1);
    }

    void AddSecondMainTriangles(std::vector<unsigned int> &indices, const int j) {
        indices.push_back(j + Chunk::CHUNK_SIZE   + 0);
        indices.push_back(j + Chunk::CHUNK_SIZE   + 1);
        indices.push_back(j + Chunk::CHUNK_SIZE*2 + 1);

        indices.push_back(j + Chunk::CHUNK_SIZE   + 0);
        indices.push_back(j + Chunk::CHUNK_SIZE*2 + 0);
        indices.push_back(j + Chunk::CHUNK_SIZE*2 + 1);
    }

    void AddFirstNorthTriangles (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) {
        indices.push_back(adjacentConstant      + 0);
        indices.push_back(adjacentConstant      + (Chunk::CHUNK_SIZE));
        indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));

        indices.push_back(adjacentConstant      + 0);
        indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
        indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE   - 1) + (i * Chunk::CHUNK_SIZE*2));
    }

    void AddSecondNorthTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) {
        indices.push_back(adjacentConstant  + (Chunk::CHUNK_SIZE*2));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_SIZE*3 - 1) + (i * Chunk::CHUNK_SIZE*2));

        indices.push_back(adjacentConstant  + (Chunk::CHUNK_SIZE*2));
        indices.push_back(adjacentConstant  + (Chunk::CHUNK_SIZE  ));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
    }

    void AddEastTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) {
        indices.push_back(adjacentConstant + 1);
        indices.push_back(adjacentConstant + 0);
        indices.push_back(chunkConstant    +     i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE));

        indices.push_back(adjacentConstant + 1);
        indices.push_back(chunkConstant    +     i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE));
        indices.push_back(chunkConstant    + 1 + i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE));
    }

    void AddNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const int adjacentConstant, const int diagonalConstant, const int chunkConstant) {
        indices.push_back(adjacentConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - (Chunk::CHUNK_SIZE));
        indices.push_back(chunkConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - 1);
        indices.push_back(diagonalConstant);
    }

    void AddNorthEastTrianglesFacingEast (std::vector<unsigned int> &indices, const int adjacentConstant, const int diagonalConstant, const int chunkConstant) {
        indices.push_back(adjacentConstant + (Chunk::CHUNK_SIZE - 1));
        indices.push_back(chunkConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - 1);
        indices.push_back(diagonalConstant);
    }

    std::array<int, 2> GetRelativeCoords(const Direction direction, std::array<int, 2> coords) {
        if (direction == Direction::north)      return std::array<int, 2> {coords[0], coords[1] + 1};
        if (direction == Direction::east)       return std::array<int, 2> {coords[0] + 1, coords[1]};
        if (direction == Direction::northeast)  return std::array<int, 2> {coords[0] + 1, coords[1] + 1};
        return coords;
    }

    auto GetIndex(const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords) {
        return std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), coords));
    }

    void DrawNorthTriangles(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        std::array<int, 2> northCoords = GetRelativeCoords(Direction::north, coords);
        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);

        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE/2; i++) {
            const int adjacentChunkConstant = (northCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
            const int adjacentConstant = adjacentChunkConstant + (i * Chunk::CHUNK_SIZE*2);

            AddFirstNorthTriangles(indices, adjacentConstant, chunkConstant, i);

            if (i != Chunk::CHUNK_SIZE/2 - 1) {
                AddSecondNorthTriangles(indices, adjacentConstant, chunkConstant, i);
            }
        }
    }

    void DrawEastTriangles(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        const std::array<int, 2> eastCoords = GetRelativeCoords(Direction::east, coords);
        const auto eastCoordsIndex = GetIndex(chunksToRender, eastCoords);

        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE - 1; i++) {
            const int adjacentChunkConstant = (eastCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
            const int adjacentConstant = adjacentChunkConstant + (i);

            AddEastTriangles(indices, adjacentConstant, chunkConstant, i);
        }
    }

    void DrawNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        const std::array<int, 2> northCoords     = GetRelativeCoords(Direction::north,       coords);
        const std::array<int, 2> northEastCoords = GetRelativeCoords(Direction::northeast,   coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

        AddNorthEastTrianglesFacingNorth(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    void DrawNorthEastTrianglesFacingEast(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        const std::array<int, 2> eastCoords      = GetRelativeCoords(Direction::east,      coords);
        const std::array<int, 2> northEastCoords = GetRelativeCoords(Direction::northeast, coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, eastCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

        AddNorthEastTrianglesFacingEast(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    void DrawNorthEastTriangles (const Map &map, std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        const std::array<int, 2> northCoords = GetRelativeCoords(Direction::north, coords);
        const std::array<int, 2> eastCoords  = GetRelativeCoords(Direction::east,  coords);

        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto eastCoordsIndex  = GetIndex(chunksToRender, eastCoords);

        if (map.ChunkExists(northCoords[0], northCoords[1])) DrawNorthEastTrianglesFacingNorth(indices, chunksToRender, coords, chunkConstant);
        if (map.ChunkExists(eastCoords [0], eastCoords [1])) DrawNorthEastTrianglesFacingEast (indices, chunksToRender, coords, chunkConstant);
    }

    void JoinAdjacentChunks(const Map &map, std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, const int chunkConstant) {
        const std::array<int, 2> northCoords      = GetRelativeCoords(Direction::north,       coords);
        const std::array<int, 2> eastCoords       = GetRelativeCoords(Direction::east,        coords);
        const std::array<int, 2> northEastCoords  = GetRelativeCoords(Direction::northeast,   coords);

        if (map.ChunkExists(northCoords    [0], northCoords    [1])) DrawNorthTriangles         (indices, chunksToRender, coords, chunkConstant);
        if (map.ChunkExists(eastCoords     [0], eastCoords     [1])) DrawEastTriangles          (indices, chunksToRender, coords, chunkConstant);
        if (map.ChunkExists(northEastCoords[0], northEastCoords[1])) DrawNorthEastTriangles(map, indices, chunksToRender, coords, chunkConstant);
    }

    void GetChunkIndices(std::vector<unsigned int> &indices, unsigned int chunkConstant) {
        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE/2; i++) {
            const int iConstant = chunkConstant + (i * Chunk::CHUNK_SIZE*2);

            for (unsigned int j = 0; j < Chunk::CHUNK_SIZE - 1; j++) {
                const int jConstant = iConstant + j;

                AddFirstMainTriangles(indices, jConstant);

                if (i != Chunk::CHUNK_SIZE/2 - 1) {
                    AddSecondMainTriangles(indices, jConstant);
                }
            }
        }
    }

    std::vector<unsigned int> GetAllIndices(const Map& map, const std::vector<std::array<int, 2>> &chunksToRender) {
        std::vector<unsigned int> indices;
        unsigned int chunkIndex = 0;
        for (const std::array<int, 2> chunkCoords : chunksToRender) {
            const int chunkConstant = (chunkIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

            GetChunkIndices(indices, chunkConstant);
            JoinAdjacentChunks(map, indices, chunksToRender, chunkCoords, chunkConstant);
            chunkIndex++;
        }

        return indices;
    }
}