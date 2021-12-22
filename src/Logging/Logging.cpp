#include "Logging.h"

#include <iostream>

void Logging::Info(const std::string &value) {
    std::cout << value << "\n";
}