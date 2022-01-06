#include "indices.h"

#include <algorithm>
#include "Chunk.h"



// TODO (at some point) clean up this disaster of a namespace that I never want to look at ever again
namespace indices {
    template<typename AT, typename ET>
    auto Contains(AT array, ET target) -> bool {;
        return (std::find(array.begin(), array.end(), target) != array.end());
    }

    auto AddFirstMainTriangles(std::vector<unsigned int> &indices, const int j) -> void {
        indices.push_back(j +                               0);
        indices.push_back(j +                               1);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 0);

        indices.push_back(j +                               1);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 1);
    }

    auto AddSecondMainTriangles(std::vector<unsigned int> &indices, const int j) -> void {
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 1);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT*2 + 1);

        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT*2 + 0);
        indices.push_back(j + Chunk::CHUNK_VERTEX_COUNT*2 + 1);
    }

    auto AddFirstNorthTriangles (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant      + 0);
        indices.push_back(adjacentConstant      + (Chunk::CHUNK_VERTEX_COUNT));
        indices.push_back(chunkConstant         + (Chunk::CHUNK_VERTEX_COUNT*2 - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));

        indices.push_back(adjacentConstant      + 0);
        indices.push_back(chunkConstant         + (Chunk::CHUNK_VERTEX_COUNT*2 - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));
        indices.push_back(chunkConstant         + (Chunk::CHUNK_VERTEX_COUNT   - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));
    }

    auto AddSecondNorthTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant  + (Chunk::CHUNK_VERTEX_COUNT*2));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_VERTEX_COUNT*2 - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_VERTEX_COUNT*3 - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));

        indices.push_back(adjacentConstant  + (Chunk::CHUNK_VERTEX_COUNT*2));
        indices.push_back(adjacentConstant  + (Chunk::CHUNK_VERTEX_COUNT  ));
        indices.push_back(chunkConstant     + (Chunk::CHUNK_VERTEX_COUNT*2 - 1) + (i * Chunk::CHUNK_VERTEX_COUNT*2));
    }

    auto AddEastTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant + 1);
        indices.push_back(adjacentConstant + 0);
        indices.push_back(chunkConstant    +     i + (Chunk::CHUNK_VERTEX_COUNT*Chunk::CHUNK_VERTEX_COUNT - Chunk::CHUNK_VERTEX_COUNT));

        indices.push_back(adjacentConstant + 1);
        indices.push_back(chunkConstant    +     i + (Chunk::CHUNK_VERTEX_COUNT*Chunk::CHUNK_VERTEX_COUNT - Chunk::CHUNK_VERTEX_COUNT));
        indices.push_back(chunkConstant    + 1 + i + (Chunk::CHUNK_VERTEX_COUNT*Chunk::CHUNK_VERTEX_COUNT - Chunk::CHUNK_VERTEX_COUNT));
    }

    auto AddNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const int adjacentConstant, 
                                          const int diagonalConstant, const int chunkConstant) -> void {
        indices.push_back(adjacentConstant + (Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT) - (Chunk::CHUNK_VERTEX_COUNT));
        indices.push_back(chunkConstant + (Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT) - 1);
        indices.push_back(diagonalConstant);
    }

    auto AddNorthEastTrianglesFacingEast (std::vector<unsigned int> &indices, const int adjacentConstant, 
                                          const int diagonalConstant, const int chunkConstant) -> void {
        indices.push_back(adjacentConstant + (Chunk::CHUNK_VERTEX_COUNT - 1));
        indices.push_back(chunkConstant + (Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT) - 1);
        indices.push_back(diagonalConstant);
    }

    auto GetRelativeCoords(const Direction direction, std::array<int, 2> coords) -> std::array<int, 2> {
        if (direction == Direction::north)      { return std::array<int, 2> {coords[0], coords[1] + 1}; }
        if (direction == Direction::east)       { return std::array<int, 2> {coords[0] + 1, coords[1]}; }
        if (direction == Direction::northeast)  { return std::array<int, 2> {coords[0] + 1, coords[1] + 1}; }
        return coords;
    }

    auto GetIndex(const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords) -> int {
        return (int)std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), coords));
    }

    auto DrawNorthTriangles(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                            const std::array<int, 2> coords, const int chunkConstant) -> void {
        std::array<int, 2> northCoords = GetRelativeCoords(Direction::north, coords);
        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);

        for (int i = 0; i < Chunk::CHUNK_VERTEX_COUNT/2; i++) {
            const int adjacentChunkConstant = (northCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);
            const int adjacentConstant = adjacentChunkConstant + (i * Chunk::CHUNK_VERTEX_COUNT*2);

            AddFirstNorthTriangles(indices, adjacentConstant, chunkConstant, i);

            if (i != Chunk::CHUNK_VERTEX_COUNT/2 - 1) {
                AddSecondNorthTriangles(indices, adjacentConstant, chunkConstant, i);
            }
        }
    }

    auto DrawEastTriangles(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                           const std::array<int, 2> coords, const int chunkConstant) -> void {
        const std::array<int, 2> eastCoords = GetRelativeCoords(Direction::east, coords);
        const auto eastCoordsIndex = GetIndex(chunksToRender, eastCoords);

        for (int i = 0; i < Chunk::CHUNK_VERTEX_COUNT - 1; i++) {
            const int adjacentChunkConstant = (eastCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);
            const int adjacentConstant = adjacentChunkConstant + (i);

            AddEastTriangles(indices, adjacentConstant, chunkConstant, i);
        }
    }

    auto DrawNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                           const std::array<int, 2> coords, const int chunkConstant) -> void {
        const std::array<int, 2> northCoords     = GetRelativeCoords(Direction::north,       coords);
        const std::array<int, 2> northEastCoords = GetRelativeCoords(Direction::northeast,   coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);

        AddNorthEastTrianglesFacingNorth(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    auto DrawNorthEastTrianglesFacingEast(std::vector<unsigned int> &indices, const std::vector<std::array<int, 2>> &chunksToRender, 
                                          const std::array<int, 2> coords, const int chunkConstant) -> void {
        const std::array<int, 2> eastCoords      = GetRelativeCoords(Direction::east,      coords);
        const std::array<int, 2> northEastCoords = GetRelativeCoords(Direction::northeast, coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, eastCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);

        AddNorthEastTrianglesFacingEast(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    auto DrawNorthEastTriangles(const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                                const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, 
                                const int chunkConstant) -> void {
        const std::array<int, 2> northCoords = GetRelativeCoords(Direction::north, coords);
        const std::array<int, 2> eastCoords  = GetRelativeCoords(Direction::east,  coords);

        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto eastCoordsIndex  = GetIndex(chunksToRender, eastCoords);

        if (Contains(chunksToRender, northCoords)) { DrawNorthEastTrianglesFacingNorth(indices, chunksToRender, coords, chunkConstant); }
        if (Contains(chunksToRender, eastCoords)) { DrawNorthEastTrianglesFacingEast (indices, chunksToRender, coords, chunkConstant); }
    }

    auto JoinAdjacentChunks(const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                            const std::vector<std::array<int, 2>> &chunksToRender, const std::array<int, 2> coords, 
                            const int chunkConstant) -> void {
        const std::array<int, 2> northCoords      = GetRelativeCoords(Direction::north,       coords);
        const std::array<int, 2> eastCoords       = GetRelativeCoords(Direction::east,        coords);
        const std::array<int, 2> northEastCoords  = GetRelativeCoords(Direction::northeast,   coords);

        if (Contains(chunksToRender, northCoords)) {
            DrawNorthTriangles(indices, chunksToRender, coords, chunkConstant);
        }

        if (Contains(chunksToRender, eastCoords)) {
            DrawEastTriangles(indices, chunksToRender, coords, chunkConstant);
        }

        if (Contains(chunksToRender, northEastCoords)) {
            DrawNorthEastTriangles(terrainStorage, indices, chunksToRender, coords, chunkConstant);
        }
    }

    auto GetChunkIndices(std::vector<unsigned int> &indices, int chunkConstant) -> void {
        for (int i = 0; i < Chunk::CHUNK_VERTEX_COUNT/2; i++) {
            const int iConstant = chunkConstant + (i * Chunk::CHUNK_VERTEX_COUNT*2);

            for (int j = 0; j < Chunk::CHUNK_VERTEX_COUNT - 1; j++) {
                const int jConstant = iConstant + j;

                AddFirstMainTriangles(indices, jConstant);

                if (i != Chunk::CHUNK_VERTEX_COUNT/2 - 1) {
                    AddSecondMainTriangles(indices, jConstant);
                }
            }
        }
    }

    auto GetAllIndices(const TerrainStorage *terrainStorage, const std::vector<std::array<int, 2>> &chunksToRender) -> std::vector<unsigned int> {
        std::vector<unsigned int> indices;
        int chunkIndex = 0;
        for (const std::array<int, 2> chunkCoords : chunksToRender) {
            const int chunkConstant = (chunkIndex * Chunk::CHUNK_VERTEX_COUNT * Chunk::CHUNK_VERTEX_COUNT);

            GetChunkIndices(indices, chunkConstant);
            JoinAdjacentChunks(terrainStorage, indices, chunksToRender, chunkCoords, chunkConstant);
            chunkIndex++;
        }

        return indices;
    }
}