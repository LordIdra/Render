#include "Shader.h"


bool exists(const std::string path) {
   ifstream file;
   file.open(path);
   return bool(file);
}


const char* Shader::ReadFile(string path) {
    if (!exists(path)) {
        Logging::Info("File not found: " + path);
    }
    ifstream file(path);
    stringstream sourceBuffer;
    sourceBuffer << file.rdbuf();
    file.close();
    return sourceBuffer.str().c_str();
}

void Shader::CheckCompile(string path) {
    int compileStatus;
    glGetShaderiv(compileStatus, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        char compileLog[512];
        glGetShaderInfoLog(id, 512, NULL, compileLog);
        Logging::Info("Shader at " + path + " failed to compile:" + compileLog);
    }
}

Shader::Shader(string path, unsigned int type) {
    id = glCreateShader(type);
    const char* source = ReadFile(path);
    Logging::Info(path);
    Logging::Info(source);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    CheckCompile(path);
}

void Shader::Attach() {
    glAttachShader(id, type);
}

void Shader::Delete() {
    glDeleteShader(id);
}