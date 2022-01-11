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
        std::vector<std::vector<Gradient>> gradients;

        const int GRADIENT_CONTAINER_CHUNK_COUNT = 8;
        constexpr int GRADIENT_CONTAINER_SIZE = Chunk::VERTEX_COUNT * GRADIENT_CONTAINER_CHUNK_COUNT;

        auto GenerateRandomGradient() -> Gradient {
            float rotationInRadians = glm::radians((float)(std::rand() % 360));
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), rotationInRadians, glm::vec3(0, 0, 1));
            return rotationMatrix * glm::vec4(1, 0, 0, 1);
        }

        auto PopulateGradientVector(std::vector<std::vector<Gradient>> &numberSet) -> void {
            for (int i = 0; i < GRADIENT_CONTAINER_SIZE; i++) {
                numberSet.emplace_back();
                for (int i = 0; i < GRADIENT_CONTAINER_SIZE; i++) {
                    numberSet[numberSet.size()-1].emplace_back(GenerateRandomGradient());
                }
            }
        }

        auto GenerateGradients() -> std::vector<std::vector<Gradient>> {
            std::vector<std::vector<Gradient>> numberSet;
            numberSet.reserve(GRADIENT_CONTAINER_SIZE);
            PopulateGradientVector(numberSet);
            return numberSet;
        }

        auto GetGradient(const ChunkCorner corner) -> Gradient {
            // normalized so it can be used to index the gradient vector table
            glm::ivec2 normalizedCorner{corner.x % (GRADIENT_CONTAINER_SIZE), corner.y % (GRADIENT_CONTAINER_SIZE)};
            return gradients[normalizedCorner.x][normalizedCorner.y];
        }
    }

    auto Initialize(const unsigned int seed) -> void {
        srand(seed);
        gradients = GenerateGradients();
    }

    auto GetHeight(ChunkCoord chunkCoord, WorldCoord worldCoord) {
        // get chunk corners
        // dot product thing
        // world domination
    }
}