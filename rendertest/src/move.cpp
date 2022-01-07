#include "move.h"

#include "keys.h"



namespace move {
    namespace {
        const glm::vec2 MOVE_SENSITIVIY     = glm::vec2(0.1, 0.1);
        const glm::vec2 MOVE_ACCELERATION   = glm::vec2(0.5, 0.5);
        const glm::vec2 MAX_MOVE_SPEED      = glm::vec2(4.0, 4.0);

        glm::vec2 moveSpeed = glm::vec2(0.0, 0.0);
    }

    auto CheckLowerBounds(float &moveSpeedDirection, float acceleration) -> void {
        const float THRESHOLD_DIVISOR = 2.0;
        if      (moveSpeedDirection >  (acceleration/THRESHOLD_DIVISOR)) { moveSpeedDirection -= acceleration; }
        else if (moveSpeedDirection < -(acceleration/THRESHOLD_DIVISOR)) { moveSpeedDirection += acceleration; }
        else                                                             { moveSpeedDirection = 0; }
    }

    auto CheckUpperBounds(float &moveSpeedDirection, float maxSpeed) -> void {
        if      (moveSpeedDirection >  (maxSpeed))  { moveSpeedDirection =  maxSpeed; }
        else if (moveSpeedDirection < -(maxSpeed))  { moveSpeedDirection = -maxSpeed; }
    }

    auto UpdateMoveSpeed(int increaseKey, int decreaseKey, float &moveSpeedDirection, float acceleration) -> bool {
        if      (keys::KeyHeldDown(increaseKey))    { moveSpeedDirection += acceleration; }
        if      (keys::KeyHeldDown(decreaseKey))    { moveSpeedDirection -= acceleration; }

        return (keys::KeyHeldDown(increaseKey) || keys::KeyHeldDown(decreaseKey));
    }

    auto Update(Camera &camera) -> void {
        camera.AddTargetX(MOVE_SENSITIVIY.x * moveSpeed.x * -cosf(camera.GetThetaXZ()));
        camera.AddTargetZ(MOVE_SENSITIVIY.x * moveSpeed.x * -sinf(camera.GetThetaXZ()));

        camera.AddTargetX(MOVE_SENSITIVIY.y * moveSpeed.y *  sinf(camera.GetThetaXZ()));
        camera.AddTargetZ(MOVE_SENSITIVIY.y * moveSpeed.y * -cosf(camera.GetThetaXZ()));

        const bool moveSpeedUpdatedX = UpdateMoveSpeed(GLFW_KEY_W, GLFW_KEY_S, moveSpeed.x, MOVE_ACCELERATION.x);
        const bool moveSpeedUpdatedY = UpdateMoveSpeed(GLFW_KEY_D, GLFW_KEY_A, moveSpeed.y, MOVE_ACCELERATION.y);

        if (!moveSpeedUpdatedX) { CheckLowerBounds(moveSpeed.x, MOVE_ACCELERATION.x); }
        if (!moveSpeedUpdatedY) { CheckLowerBounds(moveSpeed.y, MOVE_ACCELERATION.y); }

        if (moveSpeedUpdatedX)  { CheckUpperBounds(moveSpeed.x, MAX_MOVE_SPEED.x); }
        if (moveSpeedUpdatedY)  { CheckUpperBounds(moveSpeed.y, MAX_MOVE_SPEED.y); }
    }
}