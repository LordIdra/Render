#pragma once



class VBO {
private:
    unsigned int id_;

public:
    VBO();
    void Init();
    void Bind() const;
    static void Unbind();
};