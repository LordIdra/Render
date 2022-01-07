#pragma once

#include <vector>
#include "VertexAttribute.h"
#include "Vertex.h"
#include "VAO.h"
#include "EBO.h"



class Geometry {
private:
    float scaleFactor_;

    VAO vao_;
    EBO ebo_;

    unsigned int index_;

    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;

public:
    Geometry(float scale);
    
    auto AddVertexAttribute(VertexAttribute &attribute) -> void;
    auto SetVertices(std::vector<Vertex> &vertices) -> void;
    auto SetIndices(std::vector<unsigned int> &indices) -> void;
    auto Update() -> void;

    static auto EnableWireframeMode() -> void;
    static auto DisableWireframeMode() -> void;
};