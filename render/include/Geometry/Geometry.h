#pragma once

#include <vector>
#include "Vertex.h"
#include "../Memory/VAO.h"
#include "../Memory/EBO.h"



namespace Geometry {
    namespace Detail {
        extern float scaleFactor;

        extern VAO vao;
        extern EBO ebo;

        extern unsigned int index;

        extern std::vector<float> vertices;
        extern std::vector<unsigned int> indices;

        void AddVertexAttributes();
    }

    void Initialize();

    void SetScaleFactor(float scaleFactor);
    void SetVertices(std::vector<Vertex> &vertices);
    void SetIndices(std::vector<unsigned int> &indices);

    void Update();
}