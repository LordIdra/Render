#pragma once

#include <string>



class Shader {  //NOLINT - no custom copy constructor is required; id and type can be copied directly
private:
    unsigned int id_;
    const unsigned int type_;

    [[nodiscard]] static auto FileExists(const std::string &path) -> bool;
    [[nodiscard]] static auto FileAsString(const std::string &path) -> std::string;
    [[nodiscard]] static auto ReadFile(const std::string &path) -> std::string;

    auto CheckCompileSuccess(const std::string &path) const -> void;
    auto PrintCompileLog(const std::string &path) const -> void;

public:
    Shader(const std::string &path, unsigned int type);
    ~Shader();
    auto Attach(int programId) const -> void;
};