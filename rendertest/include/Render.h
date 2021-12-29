#pragma once

#include <vector>
#include <array>
#include "Geometry/Vertex.h"
#include "Shaders/Program.h"

#include "TerrainStorage.h"



namespace Render {
    namespace Detail {
        extern std::vector<Vertex> vertices;
        extern std::vector<unsigned int> indices;
        extern Program program;
    }

    void Initialize();
    void DrawChunks(TerrainStorage &terrainStorage, const std::vector<std::array<int, 2>> &chunkCoordinates);
    void Update(TerrainStorage &terrainStorage, std::vector<std::array<int, 2>> chunkCoordinates);
}