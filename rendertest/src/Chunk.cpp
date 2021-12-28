#include "Chunk.h"



const int Chunk::CHUNK_SIZE = 4;

Chunk::Chunk(const std::vector<std::vector<Vertex>> &initialVertices) 
    : vertices(initialVertices)
{}

void Chunk::SetColor(glm::vec4 &color) {
    for (std::vector<Vertex> &vertexVector : vertices) {
        for (Vertex &vertex : vertexVector) {
            vertex.color = color;
        }
    }
}

std::vector<Vertex> Chunk::GetVertices() const {
    std::vector<Vertex> oneDimensionalVertices;
    for (std::vector<Vertex> vertexVector : vertices) {
        for (Vertex vertex : vertexVector) {
            oneDimensionalVertices.push_back(vertex);
        }
    }
    return oneDimensionalVertices;
}
