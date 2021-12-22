#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <../include/glad/glad.h>
#include <../include/GLFW/glfw3.h>
#include "../Logging/Logging.h"



Shader::Shader(const std::string &path, const unsigned int type) {
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

bool FileExists(const std::string path) {
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

void Shader::Attach(const int programId) const {
    glAttachShader(programId, id);
}