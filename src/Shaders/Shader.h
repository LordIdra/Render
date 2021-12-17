#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Logging/Logging.h"

using namespace std;


class Shader {
private:
    unsigned int id;
    unsigned int type;

    const char* ReadFile(string path);
    void CheckCompile(string path);

public:
    Shader(string path, unsigned int type);
    void Attach();
    void Delete();
};