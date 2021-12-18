#include "VAO.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



VAO::VAO() {}

void VAO::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VAO would initialize that variable. Therefore, if we defined something like VAO vao; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
    glGenVertexArrays(1, &vao);
    vbo.Bind();
    vbo = VBO();
    Unbind();
    vbo.Unbind();
}

void VAO::Bind() const {
    glBindVertexArray(vao);
}

void VAO::Unbind() const {
    glBindVertexArray(0);
}

void VAO::AddVertexAttribute(unsigned int index, int size, unsigned int type, unsigned char normalised, int stride, void *offset) const {
    glVertexAttribPointer(index, size, type, normalised, stride, offset);
    glEnableVertexAttribArray(index);
}

void VAO::Data(float *data, int size) const {
    Bind();
    vbo.Data(data, size);
}
