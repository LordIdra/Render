#pragma once

#include "Shader.h"


class Program {
private:
    int id;

public:
    Program();
    void Init();
    void AddShader(Shader shader);
    void Link();
    void Use();
};