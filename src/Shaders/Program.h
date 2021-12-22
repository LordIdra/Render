#pragma once

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
};