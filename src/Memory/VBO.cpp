#include "VBO.h"

VBO::VBO() {}

void VBO::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VBO would initialize that variable. Therefore, if we defined something like VBO vbo; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
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

