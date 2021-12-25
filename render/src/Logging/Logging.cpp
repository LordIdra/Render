#include "Logging/Logging.h"

#include <iostream>



namespace Logging {
    void Info(const std::string &value) {
        std::cout << value << "\n";
    }
}