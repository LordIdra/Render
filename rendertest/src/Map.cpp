#include "Map.h"
#include <iostream>
#include <algorithm>



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

bool Map::ChunkExists(const int x, const int z) const {
    if (chunks.count(x) != 0) {
        if (chunks.at(x).count(z) != 0) {
            return true;
        }
    }
    return false;
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

std::vector<Vertex> Map::GetVertices(int x, int z) {
    std::vector<Vertex> oneDimensionalVertices;
    return chunks[x][z].GetVertices();
}

void Map::AddFirstTriangles(std::vector<unsigned int> &indices, const int jConstant) const {
    indices.push_back(jConstant +                       0);
    indices.push_back(jConstant +                       1);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 0);

    indices.push_back(jConstant +                       1);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 0);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 1);
}

void Map::AddSecondTriangles(std::vector<unsigned int> &indices, const int jConstant) const {
    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 0);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 1);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE*2 + 1);

    indices.push_back(jConstant + Chunk::CHUNK_SIZE   + 0);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE*2 + 0);
    indices.push_back(jConstant + Chunk::CHUNK_SIZE*2 + 1);
}

std::array<int, 2> Map::GetRelativeCoords(Direction direction, std::array<int, 2> coords) {
    if (direction == Direction::north)      return std::array<int, 2> {coords[0], coords[1] + 1};
    if (direction == Direction::east)       return std::array<int, 2> {coords[0] + 1, coords[1]};
    if (direction == Direction::northeast)  return std::array<int, 2> {coords[0] + 1, coords[1] + 1};
}

void Map::JoinAdjacentChunks(
        std::vector<unsigned int> &indices, 
        const std::vector<std::array<int, 2>> &chunksToRender, 
        const std::array<int, 2> coords, 
        const int chunkConstant) {
    
    // TODO SPLIT SPLIT SPLISTPSTLLSTPSTPSTISTIPPSTIPSTITITSITISI
    std::array<int, 2> northCoords = GetRelativeCoords(Direction::north, coords);

    //std::array<int, 2> northCoords      {coords[0],      coords[1] + 1};
    std::array<int, 2> eastCoords       {coords[0] + 1,  coords[1]    };
    std::array<int, 2> northEastCoords  {coords[0] + 1,  coords[1] + 1};

    // ---
    const auto northCoordsIndex =       std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), northCoords));
    const auto eastCoordsIndex =        std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), eastCoords ));
    const auto northEastCoordsIndex =   std::distance(chunksToRender.begin(), std::find(chunksToRender.begin(), chunksToRender.end(), northEastCoords ));

    // ---
    if (ChunkExists(northCoords[0], northCoords[1]) && ChunkExists(northEastCoords[0], northEastCoords[1])) {
        const int northChunkConstant =     (northCoordsIndex     * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
        const int northEastChunkConstant = (northEastCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

        // ---
        indices.push_back(northChunkConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - (Chunk::CHUNK_SIZE));
        indices.push_back(chunkConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - 1);
        indices.push_back(northEastChunkConstant);
    }

    // ---
    if (ChunkExists(eastCoords[0], eastCoords[1]) && ChunkExists(northEastCoords[0], northEastCoords[1])) {
        const int eastChunkConstant =      (eastCoordsIndex      * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
        const int northEastChunkConstant = (northEastCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

        // ---
        indices.push_back(eastChunkConstant + (Chunk::CHUNK_SIZE - 1));
        indices.push_back(chunkConstant + (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE) - 1);
        indices.push_back(northEastChunkConstant);
    }

    // ---
    if (ChunkExists(northCoords[0], northCoords[1])) {
        Chunk &northChunk = GetChunk(northCoords[0], northCoords[1]);

        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE/2; i++) {
            const int adjacentChunkConstant = (northCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
            const int adjacentConstant = adjacentChunkConstant + (i * Chunk::CHUNK_SIZE*2);

            // PREAPRE TO DIE
            // PATHETIVC MORTAL, YOU HVA EENTERED MY REALM OF DEATH1!!
            // PROCEDD AND YOU WIWLL BE CRUSSHED BENEATH MY FIST
            // ---
            indices.push_back(adjacentConstant          + 0);
            indices.push_back(adjacentConstant          + (Chunk::CHUNK_SIZE));
            indices.push_back(chunkConstant             + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));

            // ---
            indices.push_back(adjacentConstant          + 0);
            indices.push_back(chunkConstant             + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
            indices.push_back(chunkConstant             + (Chunk::CHUNK_SIZE   - 1) + (i * Chunk::CHUNK_SIZE*2));

            // ---
            if (i != Chunk::CHUNK_SIZE/2 - 1) {
                indices.push_back(adjacentConstant      + (Chunk::CHUNK_SIZE*2));
                indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
                indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE*3 - 1) + (i * Chunk::CHUNK_SIZE*2));

                indices.push_back(adjacentConstant      + (Chunk::CHUNK_SIZE*2));
                indices.push_back(adjacentConstant      + (Chunk::CHUNK_SIZE  ));
                indices.push_back(chunkConstant         + (Chunk::CHUNK_SIZE*2 - 1) + (i * Chunk::CHUNK_SIZE*2));
            }
        }
    }
    
    if (ChunkExists(eastCoords[0], eastCoords[1])) {
        Chunk &eastChunk = GetChunk(eastCoords[0], eastCoords[1]);
        glm::vec4 newColor(0.1, 0.1, 0.9, 1.0);

        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE - 1; i++) {
            const int adjacentChunkConstant = (eastCoordsIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
            const int adjacentConstant = adjacentChunkConstant + (i);

            indices.push_back(adjacentConstant + 1);
            indices.push_back(adjacentConstant + 0);
            indices.push_back(chunkConstant    + i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE)    );

            indices.push_back(adjacentConstant + 1);
            indices.push_back(chunkConstant    + i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE)    );
            indices.push_back(chunkConstant    + i + (Chunk::CHUNK_SIZE*Chunk::CHUNK_SIZE - Chunk::CHUNK_SIZE) + 1);
        }
    }
}



/* PUBLIC -------------------- */
Map::Map() {}

void Map::GenerateChunk(const int x, const int z) {
    std::vector<std::vector<Vertex>> vertices = GenerateChunkVertices(x, z);
    chunks[x][z] = Chunk(vertices);
}

std::vector<Vertex> Map::GetAllVertices(const std::vector<std::array<int, 2>> &chunksToRender) {
    std::vector<Vertex> vertices;
    for (const std::array<int, 2> chunkCoordinates : chunksToRender) {
        const std::vector<Vertex> chunkVertices = GetVertices(chunkCoordinates[0], chunkCoordinates[1]);
        vertices.insert(vertices.end(), chunkVertices.begin(), chunkVertices.end());
    }
    return vertices;
}

std::vector<unsigned int> Map::GetAllIndices(std::vector<std::array<int, 2>> &chunksToRender) {
    // TODO abstract this monster of a function
    std::vector<unsigned int> indices;
    unsigned int chunkIndex = 0;
    for (const std::array<int, 2> chunkCoords : chunksToRender) {
        const int chunkConstant = (chunkIndex * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);

        for (unsigned int i = 0; i < Chunk::CHUNK_SIZE/2; i++) {
            const int iConstant = chunkConstant + (i * Chunk::CHUNK_SIZE*2);

            for (unsigned int j = 0; j < Chunk::CHUNK_SIZE - 1; j++) {
                const int jConstant = iConstant + j;
                
                AddFirstTriangles(indices, jConstant);
                
                if (i != Chunk::CHUNK_SIZE/2 - 1) {
                    AddSecondTriangles(indices, jConstant);
                }
            }
        }

        JoinAdjacentChunks(indices, chunksToRender, chunkCoords, chunkConstant);
        chunkIndex++;
    }

    return indices;
}

