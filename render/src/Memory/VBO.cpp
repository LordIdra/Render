#include "Memory/VBO.h"

#include "Logging/logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"



/* PUBLIC -------------------- */
VBO::VBO() 
    : id_(0) {}

void VBO::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type VBO would initialize that variable. Therefore, if we defined something like VBO vbo; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults, which is NOT fun.
    glGenBuffers(1, &id_);
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
