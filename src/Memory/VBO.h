#pragma once

#include <glad/glad.h>


class VBO {
private:
    unsigned int vbo;
    unsigned int dataSize;

public:
    VBO();
    void Bind();
    void Unbind();
    void Data(const float* data, int size);
};