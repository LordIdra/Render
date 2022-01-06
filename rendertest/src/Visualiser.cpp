#include "Shaders/Shader.h"
#include "Visualiser.h"

#include "Camera/Camera.h"
#include "Camera/CameraSettings.h"
#include "Geometry/Geometry.h"
#include "TerrainStorage.h"
#include "indices.h"

#include <iostream>
#include "glm/gtx/string_cast.hpp"



void Visualiser::PrepareChunks(const std::vector<std::array<int, 2>> &chunkCoordinates) {
    vertices_ = terrainStorage_->GetAllVertices(chunkCoordinates);
    indices_ = indices::GetAllIndices(terrainStorage_, chunkCoordinates);
}

Visualiser::Visualiser(Camera *camera, TerrainStorage *terrainStorage) 
    : camera_(camera),
      terrainStorage_(terrainStorage),
      geometry_(GEOMETRY_SCALE_) {
    const int stride = 7 * sizeof(GL_FLOAT); //NOLINT - taking size of OpenGL type which is handled by GLAD, linter just sees as integer
    VertexAttribute attribute1 {
        .index = 0,
        .size = 3,
        .type = GL_FLOAT,
        .normalised = GL_FALSE,
        .stride = stride,
        .offset = nullptr
    };

    VertexAttribute attribute2 {
        .index = 1,
        .size = 4,
        .type = GL_FLOAT,
        .normalised = GL_FALSE,
        .stride = stride,
        .offset = (void*)(3*sizeof(float))  //NOLINT - a cast is required here; attribute pointer offsets accept no other type
    };

    geometry_.AddVertexAttribute(attribute1);
    geometry_.AddVertexAttribute(attribute2);
    Shader vertex("../../rendertest/resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragment("../../rendertest/resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    program_.Init();
    program_.AddShader(vertex);
    program_.AddShader(fragment);
    program_.Link();
}

void Visualiser::Update(const std::vector<std::array<int, 2>> &chunkCoordinates) {
    glm::mat4 projection = camera_->GetProjection();
    glm::mat4 view = camera_->GetView();
    program_.Use();
    program_.Set("projection", projection);
    program_.Set("view", view);
    PrepareChunks(chunkCoordinates);
    geometry_.SetVertices(vertices_);
    geometry_.SetIndices(indices_);
    geometry_.Update();
}