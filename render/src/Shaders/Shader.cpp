#include "Shaders/Shader.h"

#include "Logging/Logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>



/* PRIVATE ------------------- */
bool Shader::FileExists(const std::string &path) const {
   std::ifstream file;
   file.open(path);
   return bool(file);
}

std::string Shader::FileAsString(const std::string &path) const {
    std::ifstream file(path);
    std::stringstream sourceBuffer;
    sourceBuffer << file.rdbuf();
    file.close();
    return sourceBuffer.str();
}

std::string Shader::ReadFile(const std::string &path) const {
    if (!FileExists(path)) {
        Logging::Info("File not found: " + path);
    }
    return FileAsString(path);
}

void Shader::PrintCompileLog(const std::string &path) const {
    char compileLog[512];
    glGetShaderInfoLog(id, 512, NULL, compileLog);
    Logging::Info("Shader at " + path + " failed to compile:" + compileLog);
}

void Shader::CheckCompileSuccess(const std::string &path) const {
    int compileSuccessful;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileSuccessful);
    if (!compileSuccessful) {
        PrintCompileLog(path);
    }
}



/* PUBLIC -------------------- */
Shader::Shader(const std::string &path, const unsigned int type)
    : type(type) {
    id = glCreateShader(type);
    std::string sourceString = ReadFile(path);
    const char *source = sourceString.c_str();
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    CheckCompileSuccess(path);
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::Attach(const int programId) const {
    glAttachShader(programId, id);
}