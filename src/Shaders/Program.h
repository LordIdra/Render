#pragma once

#include "Shader.h"


class Program {
private:
    int id;

public:
    Program();
    void AddShader(Shader shader);
    void Link();
    void Use();
};