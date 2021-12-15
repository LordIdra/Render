#pragma once

#include "VBO.h"
#include <glad/glad.h>


class VAO {
private:
    VBO vbo;
    unsigned int vao;

public:
    VAO();
    void Bind();
    void Unbind();
    void AddVertexAttribute(unsigned int index, int size, unsigned int type, unsigned char normalised, int stride, const void* offset);
    void Data(const float* data, int size);
};