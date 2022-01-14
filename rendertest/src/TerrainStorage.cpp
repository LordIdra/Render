#include "TerrainStorage.h"
#include "logging.h"
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>



/* PRIVATE ------------------- */
auto TerrainStorage::Distance(float x1, float y1, float x2, float y2) {
    return sqrtf(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
}

auto TerrainStorage::CreateSquare(std::vector<ChunkCoord> &squareChunks, const ChunkCoord centreChunk, const int radius) -> void {
    ChunkCoord minimumChunk = {centreChunk.x - radius, centreChunk.y - radius};
    ChunkCoord maximumChunk = {centreChunk.x + radius, centreChunk.y + radius};
    for (int x = minimumChunk[0]; x <= maximumChunk[0]; x++) {
        for (int y = minimumChunk[1]; y <= maximumChunk[1]; y++) {
            squareChunks.emplace_back(x, y);
        }
    }
}

auto TerrainStorage::ConvertWorldCoordinatesToChunkCoordinates(const WorldCoord coord) -> ChunkCoord {
    // we don't truncate to int here because int truncates towards 0, while floor truncates towards negative infinity
    const int chunkX = std::floor((coord.x/Chunk::SIZE));
    const int chunkY = std::floor((coord.z/Chunk::SIZE));
    return ChunkCoord {chunkX, chunkY};
}

auto TerrainStorage::GetChunkCoordinatesInSquare(const WorldCoord coord, const int radius) -> std::vector<ChunkCoord> {
    ChunkCoord centreChunk = ConvertWorldCoordinatesToChunkCoordinates(coord);
    std::vector<ChunkCoord> squareChunks;
    CreateSquare(squareChunks, centreChunk, radius);
    return squareChunks;
}

auto TerrainStorage::GetChunk(const ChunkCoord coord) -> Chunk* {
    // callers are expected to do their own ChunkExists check, because if it returns
    // false, we'll want to handle it differently depending on the scenario
    return chunks_.GetPointer(coord);
}

auto TerrainStorage::GetVertices(const ChunkCoord coord) const -> std::vector<Vertex>{
    return chunks_.Get(coord).GetVertices();
}

auto TerrainStorage::AddChunk(const ChunkCoord coord, const Chunk &chunk) -> void {
    chunks_.Set(coord, chunk);
}

auto TerrainStorage::DeleteChunk(const ChunkCoord coord) -> void {
    if (ChunkExists(coord)) {
        chunks_.Delete(coord);
    }
}



/* PUBLIC -------------------- */
auto TerrainStorage::GetChunkCoordinatesInRadius(const WorldCoord coord, const int radius) -> std::vector<ChunkCoord> {
    // first we need to find a square containing all the chunks based on the input radius
    // then we go through all the chunks in the square
    //      -> find the centre of each chunk
    //      -> find the distance from the centre of each chunk to the centre of the centre chunk (yes, tongue twister)
    //      if distance > radius, add the chunk to the list
    ChunkCoord chunkCoords = ConvertWorldCoordinatesToChunkCoordinates(coord);
    std::vector<ChunkCoord> squareChunkCoordinates = GetChunkCoordinatesInSquare(coord, radius);
    std::vector<ChunkCoord> circleChunkCoordinates;
    for (ChunkCoord coordinates : squareChunkCoordinates) {
        float distance = Distance((float)coordinates.x, (float)coordinates.y, (float)chunkCoords.x, (float)chunkCoords.y);
        if (distance <= (float)radius) {
            circleChunkCoordinates.push_back(coordinates);
        }
    }
    return circleChunkCoordinates;
}

auto TerrainStorage::GenerateChunk(const ChunkCoord coord) -> void {
    // IMPORTANT this does NOT generate a chunk if it already exists
    glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0); // TODO remove this once a more permanent solution is in place (if ever lol)
    if (!ChunkExists(coord)) {
        chunks_.Set(coord, Chunk(Chunk::GenerateChunkVertices(coord, color)));
    }
}

auto TerrainStorage::GenerateChunksInRadius(const WorldCoord coord, const int radius) -> void {
    for (ChunkCoord coord : GetChunkCoordinatesInRadius(coord, radius)) {
        GenerateChunk(coord);
    }
}

auto TerrainStorage::ChunkExists(const ChunkCoord coord) const -> bool {
    return chunks_.Exists(coord);
}

auto TerrainStorage::GetAllVertices(const std::vector<ChunkCoord> &chunksToRender) -> std::vector<Vertex> {
    std::vector<Vertex> vertices;
    for (const ChunkCoord chunkCoordinates : chunksToRender) {
        const std::vector<Vertex> chunkVertices = GetVertices(chunkCoordinates);
        vertices.insert(vertices.end(), chunkVertices.begin(), chunkVertices.end());
    }
    return vertices;
}