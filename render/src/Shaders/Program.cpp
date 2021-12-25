#include "Shaders/Program.h"

#include "Logging/Logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"



/* PRIVATE ------------------- */
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



/* PUBLIC -------------------- */
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

void Program::Link() const {
    glLinkProgram(id);
    CheckLinkSuccess();
}

void Program::Use() const {
    glUseProgram(id);
}

void Program::Set(const std::string &key, const bool value) const {
    glUniform1i(glGetUniformLocation(id, key.c_str()), (int)value); 
}

void Program::Set(const std::string &key, const int value) const {
    glUniform1i(glGetUniformLocation(id, key.c_str()), value); 
}

void Program::Set(const std::string &key, const float value) const {
    glUniform1f(glGetUniformLocation(id, key.c_str()), value); 
}

void Program::Set(const std::string &key, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(id, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::mat2 &value) const {
    glUniformMatrix2fv(glGetUniformLocation(id, key.c_str()), 1, false, &value[0][0]);
}

void Program::Set(const std::string &key, const glm::mat3 &value) const {
    glUniformMatrix3fv(glGetUniformLocation(id, key.c_str()), 1, false, &value[0][0]);
}

void Program::Set(const std::string &key, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, key.c_str()), 1, false, &value[0][0]);
}