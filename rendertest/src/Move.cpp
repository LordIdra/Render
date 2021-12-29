#include "Move.h"

#include "Input/Keys.h"



namespace Move {
    namespace Detail {
        const glm::vec2 MOVE_SENSITIVIY = glm::vec2(0.1f, 0.1f);
        const glm::vec2 MOVE_ACCELERATION = glm::vec2(1.0f, 1.0f);
        const glm::vec2 MAX_MOVE_SPEED = glm::vec2(4.0f, 4.0f);

        glm::vec2 moveSpeed = glm::vec2(0.0f, 0.0f);
    }

    void CheckLowerBounds(float &moveSpeedDirection) {
        if      (moveSpeedDirection >  (Detail::MOVE_ACCELERATION.x/2.0f))  moveSpeedDirection -= Detail::MOVE_ACCELERATION.x;
        else if (moveSpeedDirection < -(Detail::MOVE_ACCELERATION.x/2.0f))  moveSpeedDirection += Detail::MOVE_ACCELERATION.x;
        else                                                                moveSpeedDirection = 0;
    }

    void CheckUpperBounds(float &moveSpeedDirection) {
        if      (moveSpeedDirection >  (Detail::MAX_MOVE_SPEED.x))          moveSpeedDirection = Detail::MAX_MOVE_SPEED.x;
        else if (moveSpeedDirection < -(Detail::MAX_MOVE_SPEED.x))          moveSpeedDirection = -Detail::MAX_MOVE_SPEED.x;
    }

    bool UpdateMoveSpeed(unsigned int increaseKey, unsigned int decreaseKey, float &moveSpeedDirection) {
        if      (Keys::KeyHeldDown(increaseKey))                            moveSpeedDirection += Detail::MOVE_ACCELERATION.x;
        if      (Keys::KeyHeldDown(decreaseKey))                            moveSpeedDirection -= Detail::MOVE_ACCELERATION.x;

        return (Keys::KeyHeldDown(increaseKey) || Keys::KeyHeldDown(decreaseKey));
    }

    void Update() {
        Camera::AddTargetX(Detail::MOVE_SENSITIVIY.x * Detail::moveSpeed.x);
        Camera::AddTargetZ(Detail::MOVE_SENSITIVIY.y * Detail::moveSpeed.y);

        const bool moveSpeedUpdatedX = UpdateMoveSpeed(GLFW_KEY_W, GLFW_KEY_S, Detail::moveSpeed.x);
        const bool moveSpeedUpdatedZ = UpdateMoveSpeed(GLFW_KEY_D, GLFW_KEY_A, Detail::moveSpeed.y);

        if (!moveSpeedUpdatedX) CheckLowerBounds(Detail::moveSpeed.x);
        if (!moveSpeedUpdatedZ) CheckLowerBounds(Detail::moveSpeed.y);

        CheckUpperBounds(Detail::moveSpeed.x);
        CheckUpperBounds(Detail::moveSpeed.y);
    }
}