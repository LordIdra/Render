#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexAttribute.h"
#include "VBO.h"



class VAO {
private:
    VBO vbo;
    unsigned int id;

public:
    VAO();
    void Init();
    void Bind() const;
    void Unbind() const;
    void AddVertexAttribute(const VertexAttribute &attribute) const;
    void Data(const std::vector<float> &data) const;
};