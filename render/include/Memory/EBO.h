#pragma once

#include <vector>



class EBO {
private:
    unsigned int id;

public:
    EBO();
    void Init();
    void Bind() const;
    void Unbind() const;
    void Data(const std::vector<unsigned int> &data) const;
};