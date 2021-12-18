#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Logging/Logging.h"



bool exists(std::string path) {
   std::ifstream file;
   file.open(path);
   return bool(file);
}


std::string Shader::ReadFile(std::string path) const {
    if (!exists(path)) {
        Logging::Info("File not found: " + path);
    }
    std::ifstream file(path);
    std::stringstream sourceBuffer;
    sourceBuffer << file.rdbuf();
    file.close();
    Logging::Info(sourceBuffer.str());
    return sourceBuffer.str();
}

void Shader::CheckCompile(std::string path) const {
    int compileStatus;
    glGetShaderiv(compileStatus, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        char compileLog[512];
        glGetShaderInfoLog(id, 512, NULL, compileLog);
        Logging::Info("Shader at " + path + " failed to compile:" + compileLog);
    }
}

Shader::Shader(std::string path, unsigned int type)
    : type(type), id(glCreateShader(type)) {
    const char *source = ReadFile(path).c_str();
    Logging::Info(path);
    Logging::Info(source);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    CheckCompile(path);
}

void Shader::Attach() const {
    glAttachShader(id, type);
}

void Shader::Delete() const {
    glDeleteShader(id);
}