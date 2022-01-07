#pragma once

#include <vector>



class EBO {
private:
    unsigned int id_;

public:
    EBO();
    auto Init() -> void;
    auto Bind() const -> void;
    static auto Unbind() -> void;
    auto Data(const std::vector<unsigned int> &data) const -> void;
};