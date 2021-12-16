#include "Program.h"

Program::Program() {}

void Program::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type Program would initialize that variable. Therefore, if we defined something like Program p; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
    id = glCreateProgram();
}

void Program::AddShader(Shader shader) {
    Use();
    shader.Attach();
}
void Program::Link() {
    int linkStatus;
    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        char linkLog[512];
        glGetProgramInfoLog(id, 512, NULL, linkLog);
        Logging::Info("Shader at failed to link: " + string(linkLog));
    }
}

void Program::Use() {
    glUseProgram(id);
}
