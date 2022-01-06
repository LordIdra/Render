#include "indices.h"

#include <algorithm>
#include "Chunk.h"
#include "units.h"



// TODO (at some point) clean up this disaster of a namespace that I never want to look at ever again
namespace indices {
    template<typename AT, typename ET>
    auto Contains(AT array, ET target) -> bool {;
        return (std::find(array.begin(), array.end(), target) != array.end());
    }

    auto AddFirstMainTriangles(std::vector<unsigned int> &indices, const int j) -> void {
        indices.push_back(j +                               0);
        indices.push_back(j +                               1);
        indices.push_back(j + Chunk::VERTEX_COUNT   + 0);

        indices.push_back(j +                               1);
        indices.push_back(j + Chunk::VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::VERTEX_COUNT   + 1);
    }

    auto AddSecondMainTriangles(std::vector<unsigned int> &indices, const int j) -> void {
        indices.push_back(j + Chunk::VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::VERTEX_COUNT   + 1);
        indices.push_back(j + Chunk::VERTEX_COUNT*2 + 1);

        indices.push_back(j + Chunk::VERTEX_COUNT   + 0);
        indices.push_back(j + Chunk::VERTEX_COUNT*2 + 0);
        indices.push_back(j + Chunk::VERTEX_COUNT*2 + 1);
    }

    auto AddFirstNorthTriangles (std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant      + 0);
        indices.push_back(adjacentConstant      + (Chunk::VERTEX_COUNT));
        indices.push_back(chunkConstant         + (Chunk::VERTEX_COUNT*2 - 1) + (i * Chunk::VERTEX_COUNT*2));

        indices.push_back(adjacentConstant      + 0);
        indices.push_back(chunkConstant         + (Chunk::VERTEX_COUNT*2 - 1) + (i * Chunk::VERTEX_COUNT*2));
        indices.push_back(chunkConstant         + (Chunk::VERTEX_COUNT   - 1) + (i * Chunk::VERTEX_COUNT*2));
    }

    auto AddSecondNorthTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant  + (Chunk::VERTEX_COUNT*2));
        indices.push_back(chunkConstant     + (Chunk::VERTEX_COUNT*2 - 1) + (i * Chunk::VERTEX_COUNT*2));
        indices.push_back(chunkConstant     + (Chunk::VERTEX_COUNT*3 - 1) + (i * Chunk::VERTEX_COUNT*2));

        indices.push_back(adjacentConstant  + (Chunk::VERTEX_COUNT*2));
        indices.push_back(adjacentConstant  + (Chunk::VERTEX_COUNT  ));
        indices.push_back(chunkConstant     + (Chunk::VERTEX_COUNT*2 - 1) + (i * Chunk::VERTEX_COUNT*2));
    }

    auto AddEastTriangles(std::vector<unsigned int> &indices, const int adjacentConstant, const int chunkConstant, const int i) -> void {
        indices.push_back(adjacentConstant + 1);
        indices.push_back(adjacentConstant + 0);
        indices.push_back(chunkConstant    +     i + (Chunk::VERTEX_COUNT*Chunk::VERTEX_COUNT - Chunk::VERTEX_COUNT));

        indices.push_back(adjacentConstant + 1);
        indices.push_back(chunkConstant    +     i + (Chunk::VERTEX_COUNT*Chunk::VERTEX_COUNT - Chunk::VERTEX_COUNT));
        indices.push_back(chunkConstant    + 1 + i + (Chunk::VERTEX_COUNT*Chunk::VERTEX_COUNT - Chunk::VERTEX_COUNT));
    }

    auto AddNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const int adjacentConstant, 
                                          const int diagonalConstant, const int chunkConstant) -> void {
        indices.push_back(adjacentConstant + (Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT) - (Chunk::VERTEX_COUNT));
        indices.push_back(chunkConstant    + (Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT) - 1);
        indices.push_back(diagonalConstant);
    }

    auto AddNorthEastTrianglesFacingEast (std::vector<unsigned int> &indices, const int adjacentConstant, 
                                          const int diagonalConstant, const int chunkConstant) -> void {
        indices.push_back(adjacentConstant + (Chunk::VERTEX_COUNT - 1));
        indices.push_back(chunkConstant + (Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT) - 1);
        indices.push_back(diagonalConstant);
    }

    auto GetRelativeCoords(const Direction direction, ChunkCoord coords) -> ChunkCoord {
        if (direction == Direction::north)      { return ChunkCoord {coords[0], coords[1] + 1}; }
        if (direction == Direction::east)       { return ChunkCoord {coords[0] + 1, coords[1]}; }
        if (direction == Direction::northeast)  { return ChunkCoord {coords[0] + 1, coords[1] + 1}; }
        return coords;
    }

    auto GetIndex(const std::vector<ChunkCoord> &chunksToRender, const ChunkCoord coords) -> int {
        return (int)std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), coords));
    }

    auto DrawNorthTriangles(std::vector<unsigned int> &indices, const std::vector<ChunkCoord> &chunksToRender, 
                            const ChunkCoord coords, const int chunkConstant) -> void {
        ChunkCoord northCoords = GetRelativeCoords(Direction::north, coords);
        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);

        for (int i = 0; i < Chunk::VERTEX_COUNT/2; i++) {
            const int adjacentChunkConstant = (northCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);
            const int adjacentConstant = adjacentChunkConstant + (i * Chunk::VERTEX_COUNT*2);

            AddFirstNorthTriangles(indices, adjacentConstant, chunkConstant, i);

            if (i != Chunk::VERTEX_COUNT/2 - 1) {
                AddSecondNorthTriangles(indices, adjacentConstant, chunkConstant, i);
            }
        }
    }

    auto DrawEastTriangles(std::vector<unsigned int> &indices, const std::vector<ChunkCoord> &chunksToRender, 
                           const ChunkCoord coords, const int chunkConstant) -> void {
        const ChunkCoord eastCoords = GetRelativeCoords(Direction::east, coords);
        const auto eastCoordsIndex = GetIndex(chunksToRender, eastCoords);

        for (int i = 0; i < Chunk::VERTEX_COUNT - 1; i++) {
            const int adjacentChunkConstant = (eastCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);
            const int adjacentConstant = adjacentChunkConstant + (i);

            AddEastTriangles(indices, adjacentConstant, chunkConstant, i);
        }
    }

    auto DrawNorthEastTrianglesFacingNorth(std::vector<unsigned int> &indices, const std::vector<ChunkCoord> &chunksToRender, 
                                           const ChunkCoord coords, const int chunkConstant) -> void {
        const ChunkCoord northCoords     = GetRelativeCoords(Direction::north,       coords);
        const ChunkCoord northEastCoords = GetRelativeCoords(Direction::northeast,   coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);

        AddNorthEastTrianglesFacingNorth(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    auto DrawNorthEastTrianglesFacingEast(std::vector<unsigned int> &indices, const std::vector<ChunkCoord> &chunksToRender, 
                                          const ChunkCoord coords, const int chunkConstant) -> void {
        const ChunkCoord eastCoords      = GetRelativeCoords(Direction::east,      coords);
        const ChunkCoord northEastCoords = GetRelativeCoords(Direction::northeast, coords);

        const auto adjacentCoordsIndex = GetIndex(chunksToRender, eastCoords);
        const auto diagonalCoordsIndex = GetIndex(chunksToRender, northEastCoords);

        const int adjacentConstant = (adjacentCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);
        const int diagonalConstant = (diagonalCoordsIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);

        AddNorthEastTrianglesFacingEast(indices, adjacentConstant, diagonalConstant, chunkConstant);
    }

    auto DrawNorthEastTriangles(const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                                const std::vector<ChunkCoord> &chunksToRender, const ChunkCoord coords, 
                                const int chunkConstant) -> void {
        const ChunkCoord northCoords = GetRelativeCoords(Direction::north, coords);
        const ChunkCoord eastCoords  = GetRelativeCoords(Direction::east,  coords);

        const auto northCoordsIndex = GetIndex(chunksToRender, northCoords);
        const auto eastCoordsIndex  = GetIndex(chunksToRender, eastCoords);

        if (Contains(chunksToRender, northCoords)) { DrawNorthEastTrianglesFacingNorth(indices, chunksToRender, coords, chunkConstant); }
        if (Contains(chunksToRender, eastCoords)) { DrawNorthEastTrianglesFacingEast (indices, chunksToRender, coords, chunkConstant); }
    }

    auto JoinAdjacentChunks(const TerrainStorage *terrainStorage, std::vector<unsigned int> &indices, 
                            const std::vector<ChunkCoord> &chunksToRender, const ChunkCoord coords, 
                            const int chunkConstant) -> void {
        const ChunkCoord northCoords      = GetRelativeCoords(Direction::north,       coords);
        const ChunkCoord eastCoords       = GetRelativeCoords(Direction::east,        coords);
        const ChunkCoord northEastCoords  = GetRelativeCoords(Direction::northeast,   coords);

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
        for (int i = 0; i < Chunk::VERTEX_COUNT/2; i++) {
            const int iConstant = chunkConstant + (i * Chunk::VERTEX_COUNT*2);

            for (int j = 0; j < Chunk::VERTEX_COUNT - 1; j++) {
                const int jConstant = iConstant + j;

                AddFirstMainTriangles(indices, jConstant);

                if (i != Chunk::VERTEX_COUNT/2 - 1) {
                    AddSecondMainTriangles(indices, jConstant);
                }
            }
        }
    }

    auto GetAllIndices(const TerrainStorage *terrainStorage, const std::vector<ChunkCoord> &chunksToRender) -> std::vector<unsigned int> {
        std::vector<unsigned int> indices;
        int chunkIndex = 0;
        for (const ChunkCoord coords : chunksToRender) {
            const int chunkConstant = (chunkIndex * Chunk::VERTEX_COUNT * Chunk::VERTEX_COUNT);

            GetChunkIndices(indices, chunkConstant);
            JoinAdjacentChunks(terrainStorage, indices, chunksToRender, coords, chunkConstant);
            chunkIndex++;
        }

        return indices;
    }
}