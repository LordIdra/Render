#include "Program.h"

#include <../include/glad/glad.h>
#include <../include/GLFW/glfw3.h>
#include "../Logging/Logging.h"



Program::Program() {}

void Program::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type Program would initialize that variable. Therefore, if we defined something like Program p; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
    id = glCreateProgram();
}

void Program::AddShader(const Shader &shader) const {
    shader.Attach(id);
}

void Program::CheckLinkSuccess() const {
    int linkSuccessful;
    glGetProgramiv(id, GL_LINK_STATUS, &linkSuccessful);
    if (!linkSuccessful) {
        PrintLinkLog();
    }
}

void Program::PrintLinkLog() const {
    char linkLog[512];
    glGetProgramInfoLog(id, 512, NULL, linkLog);
    Logging::Info("Program failed to link: " + std::string(linkLog));
}

void Program::Link() const {
    glLinkProgram(id);
    CheckLinkSuccess();
}

void Program::Use() const {
    glUseProgram(id);
}
