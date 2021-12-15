#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &vbo);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Data(const float* data, int size) {
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

