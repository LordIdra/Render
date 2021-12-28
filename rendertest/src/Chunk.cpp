#include "Chunk.h"



const int Chunk::CHUNK_SIZE = 4;

Chunk::Chunk(const std::vector<std::vector<Vertex>> &initialVertices) 
    : vertices(initialVertices)
{}

std::vector<Vertex> Chunk::GetVertices() {
    std::vector<Vertex> oneDimensionalVertices;
    for (std::vector<Vertex> vertexVector : vertices) {
        for (Vertex vertex : vertexVector) {
            oneDimensionalVertices.push_back(vertex);
        }
    }
    return oneDimensionalVertices;
}
