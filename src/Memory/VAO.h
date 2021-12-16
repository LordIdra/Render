#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"


class VAO {
private:
    VBO vbo;
    unsigned int vao;

public:
    VAO();
    void Init();
    void Bind();
    void Unbind();
    void AddVertexAttribute(unsigned int index, int size, unsigned int type, unsigned char normalised, int stride, const void* offset);
    void Data(const float* data, int size);
};