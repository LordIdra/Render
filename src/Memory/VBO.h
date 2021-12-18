#pragma once



class VBO {
private:
    unsigned int vbo;
    unsigned int dataSize;

public:
    VBO();
    void Init();
    void Bind() const;
    void Unbind() const;
    void Data(float *data, int size) const;
};