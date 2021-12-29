#pragma once

#include "Camera/Camera.h"



namespace Move {
    namespace Detail {
       extern const glm::vec2 MOVE_SENSITIVIY;
       extern const glm::vec2 MOVE_ACCELERATION;
       extern const glm::vec2 MAX_MOVE_SPEED;

       extern glm::vec2 moveSpeed;
    }

    void CheckLowerBounds(float &moveSpeedDirection);

    void CheckUpperBounds(float &moveSpeedDirection);

    bool UpdateMoveSpeed(unsigned int increaseKey, unsigned int decreaseKey, float &moveSpeedDirection);

    void Update();
}