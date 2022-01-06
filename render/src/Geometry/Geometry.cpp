#include "Geometry/Geometry.h"

#include "Window/window.h"



/* PUBLIC -------------------- */
Geometry::Geometry(float scale)
    : scaleFactor_(scale),
      index_(0) {
    vao_.Init();
    ebo_.Init();
}

auto Geometry::AddVertexAttribute(VertexAttribute &attribute) -> void {
    vao_.AddVertexAttribute(attribute);
}

auto Geometry::EnableWireframeMode() -> void {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

auto Geometry::DisableWireframeMode() -> void {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

auto Geometry::SetVertices(std::vector<Vertex> &vertices) -> void {
    vertices_.clear();
    for (Vertex &vertex : vertices) {
        vertex.position.x *= scaleFactor_;
        vertex.position.y *= scaleFactor_;
        vertex.position.z *= scaleFactor_;
        vertices_.push_back(vertex.position.x);
        vertices_.push_back(vertex.position.y);
        vertices_.push_back(vertex.position.z);
        vertices_.push_back(vertex.color.r);
        vertices_.push_back(vertex.color.g);
        vertices_.push_back(vertex.color.b);
        vertices_.push_back(vertex.color.a);
    }
}

auto Geometry::SetIndices(std::vector<unsigned int> &indices) -> void {
    indices_ = indices;
}
    
auto Geometry::Update() -> void {
    vao_.Data(vertices_);
    ebo_.Data(indices_);
    vao_.Bind();
    ebo_.Bind();
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);       
}