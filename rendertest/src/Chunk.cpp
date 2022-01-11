#include "Chunk.h"
#include <iostream>



Chunk::Chunk(const std::vector<std::vector<Vertex>> &initialVertices) 
    : vertices_(initialVertices) {}

//IMPORTANT this generates all the 'Vertex' objects in the chunk. It is NOT related to OpenGL vertices
auto Chunk::GenerateChunkVertices(const int chunkX, const int chunkY, const Color color) -> std::vector<std::vector<Vertex>> {
    std::vector<std::vector<Vertex>> vertices;

    const float chunkCoordinateX = Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)chunkX;
    const float chunkCoordinateY = Chunk::VERTEX_SPACING * (float)(Chunk::VERTEX_COUNT) * (float)chunkY;

    for (int x = 0; x < Chunk::VERTEX_COUNT; x+=2) {
        vertices.emplace_back();
        vertices.emplace_back();

        for (int y = 0; y < Chunk::VERTEX_COUNT; y++) {
            vertices[x].push_back(
                Vertex{
                    .position = WorldCoord(
                        chunkCoordinateX + float(x)*Chunk::VERTEX_SPACING,
                        (float)(rand() % 100)/200.0,
                        chunkCoordinateY + float(y)*Chunk::VERTEX_SPACING),
                    .color = color});
        }

        for (int y = 0; y < Chunk::VERTEX_COUNT; y++) {
            vertices[x+1].push_back(
                Vertex{
                    .position = WorldCoord(
                        chunkCoordinateX + float(x)*Chunk::VERTEX_SPACING + Chunk::VERTEX_SPACING,
                        (float)(rand() % 100)/200.0,
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
