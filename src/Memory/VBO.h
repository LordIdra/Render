#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class VBO {
private:
    unsigned int vbo;
    unsigned int dataSize;

public:
    VBO();
    void Init();
    void Bind();
    void Unbind();
    void Data(const float* data, int size);
};