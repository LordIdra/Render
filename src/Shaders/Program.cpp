#include "Program.h"

Program::Program() {
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
