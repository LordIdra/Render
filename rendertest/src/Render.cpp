#include "Render.h"

#include "Camera/Camera.h"
#include "Geometry/Geometry.h"
#include "TerrainStorage.h"
#include "Indices.h"



namespace Render {

    namespace Detail {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Program program;
    }

    void DrawChunks(TerrainStorage &terrainStorage, const std::vector<std::array<int, 2>> &chunkCoordinates) {
        Detail::vertices = terrainStorage.GetAllVertices(chunkCoordinates);
        Detail::indices = Indices::GetAllIndices(terrainStorage, chunkCoordinates);
    }

    void Initialize() {
        Shader vertex("../../rendertest/resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
        Shader fragment("../../rendertest/resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
        Detail::program.Init();
        Detail::program.AddShader(vertex);
        Detail::program.AddShader(fragment);
        Detail::program.Link();
    }

    void Update(TerrainStorage &terrainStorage, std::vector<std::array<int, 2>> chunkCoordinates) {
        glm::mat4 projection = Camera::GetProjection();
        glm::mat4 view = Camera::GetView();
        Detail::program.Use();
        Detail::program.Set("projection", projection);
        Detail::program.Set("view", view);
        DrawChunks(terrainStorage, chunkCoordinates);
        Geometry::SetVertices(Detail::vertices);
        Geometry::SetIndices(Detail::indices);
    }
}