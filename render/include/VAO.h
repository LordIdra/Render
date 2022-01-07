#pragma once

#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexAttribute.h"
#include "VBO.h"



class VAO {
private:
    VBO vbo_;
    unsigned int id_;

public:
    VAO();
    void Init();
    void Bind() const;
    static void Unbind();
    void AddVertexAttribute(const VertexAttribute &attribute) const;
    void Data(const std::vector<float> &data) const;
};