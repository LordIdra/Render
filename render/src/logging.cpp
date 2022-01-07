#include "logging.h"

#include <iostream>



namespace logging {
    auto Info(const std::string &value) -> void {
        std::cout << "\x1B[97m" << "[INFO] " << "\033[0m" << value << "\n";
    }

    auto Info(const char *value) -> void {
        std::cout << "\x1B[97m" << "[INFO] " << "\033[0m" << value << "\n";
    }

    auto Warn(const std::string &value) -> void {
        std::cout << "\x1B[93m" << "[WARN] " << "\033[0m"<< value << "\n";
    }

    auto Warn(const char *value) -> void {
        std::cout << "\x1B[93m" << "[WARN] " << "\033[0m"<< value << "\n";
    }

    auto Error(const std::string &value) -> void {
        std::cout << "\x1B[91m" << "[ERROR] " << "\033[0m"<< value << "\n";
    }

    auto Error(const char *value) -> void {
        std::cout << "\x1B[91m" << "[ERROR] " << "\033[0m"<< value << "\n";
    }
}