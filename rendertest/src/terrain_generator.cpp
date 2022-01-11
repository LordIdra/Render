#include "terrain_generator.h"
#include "Chunk.h"
#include "units.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include <cstdlib>
#include "logging.h"



namespace terrain_generator {
    namespace {
        std::vector<std::vector<glm::vec2>> gradients;

        const int GRADIENT_CONTAINER_CHUNKS = 8;
        constexpr int GRADIENT_CONTAINER_SIZE = Chunk::VERTEX_COUNT * GRADIENT_CHUNKS;

        auto GenerateRandomGradient() -> glm::vec2 {
            float rotationInRadians = glm::radians((float)(std::rand() % 360));
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), rotationInRadians, glm::vec3(0, 0, 1));
            return rotationMatrix * glm::vec4(1, 0, 0, 1);
        }

        auto PopulateGradientVector(std::vector<std::vector<glm::vec2>> &numberSet) -> void {
            for (int i = 0; i < SIZE; i++) {
                numberSet.emplace_back();
                for (int i = 0; i < SIZE; i++) {
                    numberSet[numberSet.size()-1].emplace_back(GenerateRandomGradient());
                }
            }
        }

        auto GenerateGradients() -> std::vector<std::vector<glm::vec2>> {
            std::vector<std::vector<glm::vec2>> numberSet;
            numberSet.reserve(GRADIENT_CONTAINER_SIZE);
            PopulateGradientVector(numberSet);
            return numberSet;
        }
    }

    auto Initialize(const unsigned int seed) -> void {
        srand(seed);
        gradients = GenerateGradients();
    }

    auto GetGradient(const ChunkCorner corner) -> float {
        corner.x %= (GRADIENT_CONTAINER_SIZE);
    }
}