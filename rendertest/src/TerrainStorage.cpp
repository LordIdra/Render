#include "TerrainStorage.h"
#include "Logging/logging.h"
#include <array>
#include <cmath>
#include <iostream>
#include <string>



/* PRIVATE ------------------- */
auto TerrainStorage::Distance(float x1, float y1, float x2, float y2) {
    return sqrtf(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
}

auto TerrainStorage::CreateSquare(std::vector<ChunkCoord> &squareChunks, const ChunkCoord centreChunk, const int radius) -> void {
    ChunkCoord minimumChunk = {centreChunk[0] - radius, centreChunk[1] - radius};
    ChunkCoord maximumChunk = {centreChunk[0] + radius, centreChunk[1] + radius};
    for (int x = minimumChunk[0]; x <= maximumChunk[0]; x++) {
        for (int y = minimumChunk[1]; y <= maximumChunk[1]; y++) {
            squareChunks.push_back(ChunkCoord {x, y});
        }
    }
}

auto TerrainStorage::ConvertWorldCoordinatesToChunkCoordinates(const float x, const float y) -> ChunkCoord {
    // we don't truncate to int here because int truncates towards 0, while floor truncates towards negative infinity
    const int CHUNK_X = std::floor((x/Chunk::SIZE));
    const int CHUNK_Y = std::floor((y/Chunk::SIZE));
    return ChunkCoord {CHUNK_X, CHUNK_Y};
}

auto TerrainStorage::GetChunkCoordinatesInSquare(const float worldX, const float worldY, const int radius) -> std::vector<ChunkCoord> {
    ChunkCoord centreChunk = ConvertWorldCoordinatesToChunkCoordinates(worldX, worldY);
    std::vector<ChunkCoord> squareChunks;
    CreateSquare(squareChunks, centreChunk, radius);
    return squareChunks;
}

auto TerrainStorage::GetChunk(const int chunkX, const int chunkY) -> Chunk* {
    // callers are expected to do their own ChunkExists check, because if it returns
    // false, we'll want to handle it differently depending on the scenario
    return &chunks_.at(chunkX).at(chunkY);
}

auto TerrainStorage::GetVertices(const int x, const int y) const -> std::vector<Vertex>{
    return chunks_.at(x).at(y).GetVertices();
}

auto TerrainStorage::AddChunk(const int chunkX, const int chunkY, const Chunk &chunk) -> void {
    chunks_[chunkX][chunkY] = chunk;
}

auto TerrainStorage::DeleteChunk(const int chunkX, const int chunkY) -> void {
    if (ChunkExists(chunkX, chunkY)) {
        chunks_[chunkX].erase(chunkY);
    }
}



/* PUBLIC -------------------- */
auto TerrainStorage::GetChunkCoordinatesInRadius(const float worldX, const float worldY, const int radius) -> std::vector<ChunkCoord> {
    ChunkCoord chunkCoords = ConvertWorldCoordinatesToChunkCoordinates(worldX, worldY);
    std::vector<ChunkCoord> squareChunkCoordinates = GetChunkCoordinatesInSquare(worldX, worldY, radius);
    std::vector<ChunkCoord> circleChunkCoordinates;
    for (ChunkCoord coordinates : squareChunkCoordinates) {
        float distance = Distance((float)coordinates[0], (float)coordinates[1], (float)chunkCoords[0], (float)chunkCoords[1]);
        if (distance <= (float)radius) {
            circleChunkCoordinates.push_back(coordinates);
        }
    }
    return circleChunkCoordinates;
    // first we need to find a square containing all the chunks based on the input radius
    // then we go through all the chunks in the square
    //      -> find the centre of each chunk
    //      -> find the distance from the centre of each chunk to the centre of the centre chunk (yes, tongue twister)
    //      if distance > radius, add the chunk to the list
}

auto TerrainStorage::GenerateChunk(const int chunkX, const int chunkY) -> void {
    // IMPORTANT this does NOT generate a chunk if it already exists
    glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0); //TODO remove this once a more permanent solution is in place (if ever lol)
    if (!ChunkExists(chunkX, chunkY)) {
        chunks_[chunkX][chunkY] = Chunk(Chunk::GenerateChunkVertices(chunkX, chunkY, color));
    }
}

auto TerrainStorage::GenerateChunksInRadius(const float worldX, const float worldY, const int radius) -> void {
    for (ChunkCoord coord : GetChunkCoordinatesInRadius(worldX, worldY, radius)) {
        GenerateChunk(coord[0], coord[1]);
    }
}

auto TerrainStorage::ChunkExists(const int chunkX, const int chunkY) const -> bool {
    if (chunks_.count(chunkX) != 0) {
        if (chunks_.at(chunkX).count(chunkY) != 0) {
            return true;
        }
    }
    return false;
}

auto TerrainStorage::GetAllVertices(const std::vector<ChunkCoord> &chunksToRender) -> std::vector<Vertex> {
    std::vector<Vertex> vertices;
    for (const ChunkCoord chunkCoordinates : chunksToRender) {
        const std::vector<Vertex> chunkVertices = GetVertices(chunkCoordinates[0], chunkCoordinates[1]);
        vertices.insert(vertices.end(), chunkVertices.begin(), chunkVertices.end());
    }
    return vertices;
}