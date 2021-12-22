#pragma once



class VBO {
private:
    unsigned int id;

public:
    VBO();
    void Init();
    void Bind() const;
    void Unbind() const;
};