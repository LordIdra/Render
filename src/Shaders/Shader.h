#pragma once

#include <string>



class Shader {
private:
    const unsigned int id;
    const unsigned int type;

    std::string ReadFile(std::string path) const;
    void CheckCompile(std::string path) const;

public:
    Shader(std::string path, unsigned int type);
    void Attach() const;
    void Delete() const;
};