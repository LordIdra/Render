#include "Map.h"



/* PRIVATE ------------------- */
std::vector<std::vector<Vertex>> Map::GenerateChunkVertices(const int chunkX, const int chunkZ) const {
    glm::vec4 vertexColor = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);
    std::vector<std::vector<Vertex>> vertices;

    for (int x = 0; x < Chunk::CHUNK_SIZE; x+=2) {
        vertices.push_back(std::vector<Vertex>());
        vertices.push_back(std::vector<Vertex>());

        for (int z = 0; z < Chunk::CHUNK_SIZE; z++) {
            vertices[x].push_back(
                Vertex{
                    position: glm::vec3(
                        (Chunk::CHUNK_SIZE * chunkX) + float(x),
                        (rand() % 100)/200.0f,
                        (Chunk::CHUNK_SIZE * chunkZ) + float(z)),
                    color: vertexColor});
        }

        for (int z = 0; z < Chunk::CHUNK_SIZE; z++) {
            vertices[x+1].push_back(
                Vertex{
                    position: glm::vec3(
                        (Chunk::CHUNK_SIZE * chunkX) + float(x) + 1.0f,
                        (rand() % 100)/200.0f,
                        (Chunk::CHUNK_SIZE * chunkZ) + float(z) + 0.5f),
                    color: vertexColor});
        }
    }
    return vertices;
}

Chunk &Map::GetChunk(const int x, const int z) {
    // callers are expected to do their own ChunkExists check, because if it returns
    // false, we'll want to handle it differently depending on the scenario
    return chunks.at(x).at(z);
}

void Map::AddChunk(const int x, const int z, Chunk chunk) {
    chunks[x][z] = chunk;
}

void Map::DeleteChunk(const int x, const int z) {
    if (ChunkExists(x, z)) {
        chunks[x].erase(z);
    }
}

std::vector<Vertex> Map::GetVertices(const int x, const int z) const {
    std::vector<Vertex> oneDimensionalVertices;
    return chunks.at(x).at(z).GetVertices();
}





/* PUBLIC -------------------- */
Map::Map() {}

void Map::GenerateChunk(const int x, const int z) {
    std::vector<std::vector<Vertex>> vertices = GenerateChunkVertices(x, z);
    chunks[x][z] = Chunk(vertices);
}

bool Map::ChunkExists(const int x, const int z) const {
    if (chunks.count(x) != 0) {
        if (chunks.at(x).count(z) != 0) {
            return true;
        }
    }
    return false;
}

std::vector<Vertex> Map::GetAllVertices(const std::vector<std::array<int, 2>> &chunksToRender) {
    std::vector<Vertex> vertices;
    for (const std::array<int, 2> chunkCoordinates : chunksToRender) {
        const std::vector<Vertex> chunkVertices = GetVertices(chunkCoordinates[0], chunkCoordinates[1]);
        vertices.insert(vertices.end(), chunkVertices.begin(), chunkVertices.end());
    }
    return vertices;
}