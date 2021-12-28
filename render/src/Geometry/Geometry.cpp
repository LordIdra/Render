#include "Geometry/Geometry.h"

#include "Window/Window.h"



namespace Geometry {
    namespace Detail {
        const float SCALE_FACTOR = 1.0;
        VAO vao;
        EBO ebo;
        unsigned int index;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        void AddVertexAttributes() {
            vao.AddVertexAttribute(VertexAttribute{
                index: 0,
                size: 3,
                type: GL_FLOAT,
                normalised: GL_FALSE,
                stride: 7 * sizeof(GL_FLOAT),
                offset: (void*)0
            });

            vao.AddVertexAttribute(VertexAttribute{
                index: 1,
                size: 4,
                type: GL_FLOAT,
                normalised: GL_FALSE,
                stride: 7 * sizeof(GL_FLOAT),
                offset: (void*)(3*sizeof(float))
            });
        }
    }

    void Initialize() {
        Detail::vao.Init();
        Detail::ebo.Init();
        Detail::AddVertexAttributes();
    }

    void SetVertices(std::vector<Vertex> &vertices) {
        Detail::vertices.clear();
        for (Vertex &vertex : vertices) {
            vertex.position.x *= Detail::SCALE_FACTOR;
            vertex.position.y *= Detail::SCALE_FACTOR;
            vertex.position.z *= Detail::SCALE_FACTOR;
            Detail::vertices.push_back(vertex.position.x);
            Detail::vertices.push_back(vertex.position.y);
            Detail::vertices.push_back(vertex.position.z);
            Detail::vertices.push_back(vertex.color.r);
            Detail::vertices.push_back(vertex.color.g);
            Detail::vertices.push_back(vertex.color.b);
            Detail::vertices.push_back(vertex.color.a);
        }
    }

    void SetIndices(std::vector<unsigned int> &indices) {
        Detail::indices = indices;
    }
    
    void Update() {
        Detail::vao.Data(Detail::vertices);
        Detail::ebo.Data(Detail::indices);
        Detail::vao.Bind();
        Detail::ebo.Bind();
        glDrawElements(GL_TRIANGLES, Detail::indices.size(), GL_UNSIGNED_INT, 0);       
    }
}