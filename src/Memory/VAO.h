#pragma once

#include "VBO.h"



class VAO {
private:
    VBO vbo;
    unsigned int vao;

public:
    VAO();
    void Init();
    void Bind() const;
    void Unbind() const;
    void AddVertexAttribute(unsigned int index,  int size,  unsigned int type,  unsigned char normalised,  int stride,  void *offset) const;
    void Data( float *data,  int size) const;
};