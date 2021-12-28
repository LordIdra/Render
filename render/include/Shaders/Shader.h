#pragma once

#include <string>



class Shader {
private:
    unsigned int id;
    const unsigned int type;

    bool FileExists(const std::string &path) const;
    std::string FileAsString(const std::string &path) const;
    std::string ReadFile(const std::string &path) const;
    void CheckCompileSuccess(const std::string &path) const;
    void PrintCompileLog(const std::string &path) const;

public:
    Shader(const std::string &path, const unsigned int type);
    ~Shader();
    void Attach(const int programId) const;
};