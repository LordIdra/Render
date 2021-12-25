#pragma once

#include "glm/glm.hpp"
#include "Shader.h"



class Program {
private:
    int id;
    void CheckLinkSuccess() const;
    void PrintLinkLog() const;

public:
    Program();
    void Init();
    void AddShader(const Shader &shader) const;
    void Link() const;
    void Use() const;

    void Set(const std::string &key, const bool value) const;
    void Set(const std::string &key, const int value) const;
    void Set(const std::string &key, const float value) const;
    void Set(const std::string &key, const glm::vec2 &value) const;
    void Set(const std::string &key, const glm::vec3 &value) const;
    void Set(const std::string &key, const glm::vec4 &value) const;
    void Set(const std::string &key, const glm::mat2 &value) const;
    void Set(const std::string &key, const glm::mat3 &value) const;
    void Set(const std::string &key, const glm::mat4 &value) const;
};