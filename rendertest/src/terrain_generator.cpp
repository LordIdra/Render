#include "terrain_generator.h"
#include "Chunk.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <array>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "logging.h"
#include "util.h"


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
            glm::ivec2 normalizedCorner{std::abs(corner.x % (GRADIENT_CONTAINER_SIZE)), std::abs(corner.y % (GRADIENT_CONTAINER_SIZE))};
            return gradients[normalizedCorner.x][normalizedCorner.y];
        }

        auto GetChunkCorners(ChunkCoord coord) -> std::array<ChunkCoord, 4> {
            return std::array<ChunkCoord, 4> {coord, coord + ChunkCoord(0, 1), coord + ChunkCoord(1, 0), coord + ChunkCoord(1, 1)};
        }

        auto SubtractPlaneCoord(PlaneCoord from, PlaneCoord coord) -> PlaneCoord {
            return from - coord;
        }

        auto GetGradientVectors(std::array<ChunkCoord, 4> corners) -> std::array<glm::vec2, 4> {
            return std::array<Gradient, 4> { GetGradient(corners[0]), GetGradient(corners[1]), GetGradient(corners[2]), GetGradient(corners[3]) };
        }

        auto GetCornerVectors(std::array<ChunkCoord, 4> corners, PlaneCoord centre) -> std::array<PlaneCoord, 4> {
            std::array<PlaneCoord, 4> cornersAsPlaneCoords = {};
            for (int i = 0; i < 4; i++) {
                cornersAsPlaneCoords[i] = SubtractPlaneCoord(centre, cornersAsPlaneCoords.at(i));   //NOLINT at() does not allow assignment
            }
            return cornersAsPlaneCoords;
        }

        auto GetDotProducts(std::array<PlaneCoord, 4> term1, std::array<PlaneCoord, 4> term2) -> std::array<float, 4> {
            std::array<float, 4> cornersAsPlaneCoords = {};
            for (int i = 0; i < 4; i++) {
                cornersAsPlaneCoords[i] = glm::dot(term1.at(i), term2.at(i)); //NOLINT at() does not allow assignment
            }
            return cornersAsPlaneCoords;
        }

        auto Blend(float x) -> float {
            return (6*powf(x, 5)) - (15*powf(x, 4)) + (10*powf(x, 3));
        }

        auto Interpolate(std::array<float, 4> dotProducts, PlaneCoord coords) -> float {
            float fu = Blend((float)coords.x);
            float fv = Blend((float)coords.y);
            float nx0 = ((1-fu)*dotProducts[0]) + ((fu)*dotProducts[1]);
            float nx1 = ((1-fu)*dotProducts[2]) + ((fu)*dotProducts[3]);
            return (((1-fv)*nx0) + ((fv)*nx1));
        }
    }

    auto Initialize(const unsigned int seed) -> void {
        srand(seed);
        gradients = GenerateGradients();
    }

    auto GetHeight(ChunkCoord chunkCoord, PlaneCoord planeCoord) -> float {
        std::array<ChunkCoord, 4> corners = GetChunkCorners(chunkCoord);
        //std::array<Gradient, 4> gradientVectors = GetGradientVectors(corners);
        std::array<Gradient, 4> gradientVectors {Gradient(1.0, 0.0), Gradient(0.0, 1.0), Gradient(0.707, 0.707), Gradient(0.0, -1.0)};
        std::array<PlaneCoord, 4> cornerVectors = GetCornerVectors(corners, planeCoord);
        std::array<float, 4> dotProducts = GetDotProducts(gradientVectors, cornerVectors);
        return Interpolate(dotProducts, planeCoord) * 8;
    }
}