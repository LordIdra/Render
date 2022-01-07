#include "Shader.h"

#include "logging.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>



/* PRIVATE ------------------- */
auto Shader::FileExists(const std::string &path) -> bool {
   std::ifstream file;
   file.open(path);
   return bool(file);
}

auto Shader::FileAsString(const std::string &path) -> std::string {
    std::ifstream file(path);
    std::stringstream sourceBuffer;
    sourceBuffer << file.rdbuf();
    file.close();
    return sourceBuffer.str();
}

auto Shader::ReadFile(const std::string &path) -> std::string {
    if (!FileExists(path)) {
        logging::Error("File not found: " + path);
    }
    return FileAsString(path);
}

auto Shader::PrintCompileLog(const std::string &path) const -> void {
    const unsigned int LOG_LENGTH = 1024;
    std::string compileLog;
    compileLog.reserve(LOG_LENGTH);
    glGetShaderInfoLog(id_, LOG_LENGTH, nullptr, &compileLog[0]);
    logging::Error("Shader at " + path + " failed to compile:" + compileLog);
}

auto Shader::CheckCompileSuccess(const std::string &path) const -> void {
    int compileSuccessful = 0;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compileSuccessful);
    if (!compileSuccessful) {
        PrintCompileLog(path);
    }
}



/* PUBLIC -------------------- */
Shader::Shader(const std::string &path, const unsigned int type)
    : id_(glCreateShader(type)), 
      type_(type) {
    
    std::string sourceString = ReadFile(path);
    const char *source = sourceString.c_str();
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);
    CheckCompileSuccess(path);
}

Shader::~Shader() {
    glDeleteShader(id_);
}

void Shader::Attach(const int programId) const {
    glAttachShader(programId, id_);
}