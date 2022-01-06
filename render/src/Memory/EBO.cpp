#include "Memory/EBO.h"

#include "Logging/logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"



/* PUBLIC -------------------- */
EBO::EBO()
    : id_(0) {}

auto EBO::Init() -> void {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VBO would initialize that variable. Therefore, if we defined something like VBO vbo; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults, which is NOT fun.
    glGenBuffers(1, &id_);
}

auto EBO::Bind() const -> void {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

auto EBO::Unbind() -> void {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::Data(const std::vector<unsigned int> &data) const -> void {
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long)data.size() * sizeof(unsigned int), &data[0], GL_DYNAMIC_DRAW); //NOLINT - a cast is necessary here and has almost no 
                                                                                                                // risk at all of overflow (petabyte scale computing, anyone?)
    Unbind();
}
