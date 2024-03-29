#include "VAO.h"

#include "logging.h"



/* PUBLIC -------------------- */
VAO::VAO()
    : id_(0) {}

void VAO::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VAO would initialize that variable. Therefore, if we defined something like VAO vao; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults, which is NOT fun.
    glGenVertexArrays(1, &id_);
    Bind();
    vbo_ = VBO();
    vbo_.Init();
    vbo_.Bind();
    Unbind();
}

void VAO::Bind() const {
    glBindVertexArray(id_);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::AddVertexAttribute(const VertexAttribute &attribute) const {
    Bind();
    glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalised, attribute.stride, attribute.offset);
    glEnableVertexAttribArray(attribute.index);
    Unbind();
}

void VAO::Data(const std::vector<float> &data) const {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_DYNAMIC_DRAW);  //NOLINT - a cast is necessary here, no risk of overflow
    Unbind();
}
