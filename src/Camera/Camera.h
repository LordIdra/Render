#pragma once

#include "../../include/glm/glm.hpp"



namespace Camera {
    namespace Detail {
        const glm::vec3 vertical;
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 back;
        glm::vec3 up;
        glm::vec3 right;

        glm::mat4 view;
        glm::mat4 projection;

        void UpdateDirection();
    }

    void SetPosition(float x, float y, float z);
    void SetTarget(float x, float y, float z);
}