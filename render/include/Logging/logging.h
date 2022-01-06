#pragma once

#include <string>



namespace logging {
    auto Info   (const std::string &value) -> void;
    auto Warning(const std::string &value) -> void;
    auto Error  (const std::string &value) -> void;
}