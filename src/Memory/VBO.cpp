#include "VBO.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



VBO::VBO() {}

void VBO::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VBO would initialize that variable. Therefore, if we defined something like VBO vbo; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
    glGenBuffers(1, &vbo);
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Data(float *data, int size) const {
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

