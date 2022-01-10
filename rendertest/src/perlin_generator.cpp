#include "perlin_generator.h"

#include <vector>
#include <cstdlib>



namespace perlin_generator {
    auto Initialize(const unsigned int seed) -> void {
        srand(seed);
    }

    auto GenerateNumberSet(const int size, const int range, const int precision) -> std::vector<float> {
        std::vector<float> numberSet;
        numberSet.reserve(size);
        for (int i = 0; i < size; i++) {
            numberSet.push_back((float)(rand() % (range * precision)) / (float)precision);
        }
        return numberSet;
    }
}