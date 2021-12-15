#include "VAO.h"


VAO::VAO() {
    glGenVertexArrays(1, &vao);
    vbo.Bind();
    vbo = VBO();
    Unbind();
    vbo.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(vao);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::AddVertexAttribute(unsigned int index, int size, unsigned int type, unsigned char normalised, int stride, const void* offset) {
    glVertexAttribPointer(index, size, type, normalised, stride, offset);
    glEnableVertexAttribArray(index);
}

void VAO::Data(const float* data, int size) {
    Bind();
    vbo.Data(data, size);
}
