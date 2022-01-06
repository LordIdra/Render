#pragma once

#include <vector>
#include <array>
#include "Camera/Camera.h"
#include "Geometry/Geometry.h"
#include "Shaders/Program.h"
#include "TerrainStorage.h"



class Visualiser {
private:
    const float GEOMETRY_SCALE_ = 1.0;
    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    Program program_;
    Geometry geometry_;
    Camera *const camera_;
    TerrainStorage *const terrainStorage_;

    void PrepareChunks(const std::vector<ChunkCoord> &chunkCoordinates);
    
public:
    Visualiser(Camera *camera, TerrainStorage *terrainStorage);
    void Update(const std::vector<ChunkCoord> &chunkCoordinates);
};