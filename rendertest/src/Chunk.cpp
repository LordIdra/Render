#include "Chunk.h"
#include "terrain_generator.h"
#include "util.h"
#include <iostream>



Chunk::Chunk(const std::vector<std::vector<Vertex>> &initialVertices) 
    : vertices_(initialVertices) {}

auto Chunk::PlaneCoordToChunkCoord(const PlaneCoord coord) -> ChunkCoord {
    // we don't truncate to int here because int truncates towards 0, while floor truncates towards negative infinity
    const int chunkX = std::floor((coord.x/Chunk::SIZE));
    const int chunkY = std::floor((coord.y/Chunk::SIZE));
    return ChunkCoord {chunkX, chunkY};
}

auto Chunk::ChunkCoordToPlaneCoord(const ChunkCoord coord) -> PlaneCoord {
    // we don't truncate to int here because int truncates towards 0, while floor truncates towards negative infinity
    const float chunkX = (float)coord.x*Chunk::SIZE;
    const float chunkY = (float)coord.y*Chunk::SIZE;
    return PlaneCoord {chunkX, chunkY};
}

//IMPORTANT this generates all the 'Vertex' objects in the chunk. It is NOT related to OpenGL vertices
auto Chunk::GenerateChunkVertices(const ChunkCoord &coord, const Color color) -> std::vector<std::vector<Vertex>> {
    std::vector<std::vector<Vertex>> vertices;

    const float chunkCoordinateX = Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)coord.x;
    const float chunkCoordinateY = Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)coord.y;

    const glm::vec2 worldCoord(
        Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)coord.x,
        Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)coord.y);

    for (int x = 0; x < Chunk::VERTEX_COUNT; x+=2) {
        vertices.emplace_back();
        vertices.emplace_back();

        for (int y = 0; y < Chunk::VERTEX_COUNT; y++) {
            float planex = float(x) / float(Chunk::VERTEX_COUNT);
            float planey = float(y) / float(Chunk::VERTEX_COUNT);
            vertices[x].push_back(
                Vertex{
                    .position = WorldCoord(
                        chunkCoordinateX + float(x)*Chunk::VERTEX_SPACING,
                        terrain_generator::GetHeight(coord, PlaneCoord(planex, planey)), //(float)(rand() % 100)/200.0,
                        chunkCoordinateY + float(y)*Chunk::VERTEX_SPACING),
                    .color = color});
        }

        for (int y = 0; y < Chunk::VERTEX_COUNT; y++) {
            float planex = float(x) / float(Chunk::VERTEX_COUNT);
            float planey = float(y) / float(Chunk::VERTEX_COUNT);
            vertices[x+1].push_back(
                Vertex{
                    .position = WorldCoord(
                        chunkCoordinateX + float(x)*Chunk::VERTEX_SPACING + Chunk::VERTEX_SPACING,
                        terrain_generator::GetHeight(coord, PlaneCoord(planex, planey)), //(float)(rand() % 100)/200.0,
                        chunkCoordinateY + float(y)*Chunk::VERTEX_SPACING + Chunk::VERTEX_SPACING/2),
                    .color = color});
        }
    }
    return vertices;
}

auto Chunk::SetColor(Color color) -> void {
    for (std::vector<Vertex> &vertexArray : vertices_) {
        for (Vertex &vertex : vertexArray) {
            vertex.color = color;
        }
    }
}

auto Chunk::GetVertices() const -> std::vector<Vertex> {
    std::vector<Vertex> oneDimensionalVertices;
    for (const std::vector<Vertex> &vertexVector : vertices_) {
        for (const Vertex &vertex : vertexVector) {
            oneDimensionalVertices.push_back(vertex);
        }
    }
    return oneDimensionalVertices;
}
