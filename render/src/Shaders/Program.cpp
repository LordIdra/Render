#include "Shaders/Program.h"

#include "Logging/logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>



/* PRIVATE ------------------- */
void Program::CheckLinkSuccess() const {
    int linkSuccessful = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &linkSuccessful);
    if (!linkSuccessful) {
        PrintLinkLog();
    }
}

void Program::PrintLinkLog() const {
    const unsigned int LOG_LENGTH = 1024;
    std::string linkLog;
    linkLog.reserve(LOG_LENGTH);
    glGetProgramInfoLog(id_, LOG_LENGTH, nullptr, &linkLog[0]);
    logging::Error("Program failed to link: " + linkLog);
}



/* PUBLIC -------------------- */
Program::Program()
    : id_(0) {}

void Program::Init() {
    // Why does this exist? The reason is that if this was in the constructor, forward-declaring a variable
    // of type Program would initialize that variable. Therefore, if we defined something like Program p; in the
    // main file, it would try to call the constructor before main() is called, so GLAD has not had a chance
    // to initialize and the glxxxx() commands would cause segmentation faults
    id_ = glCreateProgram();
}

void Program::AddShader(const Shader &shader) const {
    shader.Attach(id_);
}

void Program::Link() const {
    glLinkProgram(id_);
    CheckLinkSuccess();
}

void Program::Use() const {
    glUseProgram(id_);
}

void Program::Set(const std::string &key, const bool value) const {
    glUniform1i(glGetUniformLocation(id_, key.c_str()), (int)value); 
}

void Program::Set(const std::string &key, const int value) const {
    glUniform1i(glGetUniformLocation(id_, key.c_str()), value); 
}

void Program::Set(const std::string &key, const float value) const {
    glUniform1f(glGetUniformLocation(id_, key.c_str()), value); 
}

void Program::Set(const std::string &key, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(id_, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id_, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id_, key.c_str()), 1, &value[0]);
}

void Program::Set(const std::string &key, const glm::mat2 &value) const {
    glUniformMatrix2fv(glGetUniformLocation(id_, key.c_str()), 1, false, &value[0][0]);
}

void Program::Set(const std::string &key, const glm::mat3 &value) const {
    glUniformMatrix3fv(glGetUniformLocation(id_, key.c_str()), 1, false, &value[0][0]);
}

void Program::Set(const std::string &key, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, key.c_str()), 1, false, &value[0][0]);
}