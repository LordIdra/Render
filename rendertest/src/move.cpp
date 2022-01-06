#include "move.h"

#include "Input/keys.h"



namespace move {
    namespace {
        const glm::vec2 MOVE_SENSITIVIY = glm::vec2(0.1, 0.1);
        const glm::vec2 MOVE_ACCELERATION = glm::vec2(1.0, 1.0);
        const glm::vec2 MAX_MOVE_SPEED = glm::vec2(4.0, 4.0);

        glm::vec2 moveSpeed = glm::vec2(0.0, 0.0);
    }

    auto CheckLowerBounds(float &moveSpeedDirection) -> void {
        const float THRESHOLD_DIVISOR = 2.0;
        if      (moveSpeedDirection >  (MOVE_ACCELERATION.x/THRESHOLD_DIVISOR)) { moveSpeedDirection -= MOVE_ACCELERATION.x; }
        else if (moveSpeedDirection < -(MOVE_ACCELERATION.x/THRESHOLD_DIVISOR)) { moveSpeedDirection += MOVE_ACCELERATION.x; }
        else                                                                    { moveSpeedDirection = 0; }
    }

    auto CheckUpperBounds(float &moveSpeedDirection) -> void{
        if      (moveSpeedDirection >  (MAX_MOVE_SPEED.x))  { moveSpeedDirection = MAX_MOVE_SPEED.x; }
        else if (moveSpeedDirection < -(MAX_MOVE_SPEED.x))  { moveSpeedDirection = -MAX_MOVE_SPEED.x; }
    }

    auto UpdateMoveSpeed(int increaseKey, int decreaseKey, float &moveSpeedDirection) -> bool{
        if      (keys::KeyHeldDown(increaseKey))    { moveSpeedDirection += MOVE_ACCELERATION.x; }
        if      (keys::KeyHeldDown(decreaseKey))    { moveSpeedDirection -= MOVE_ACCELERATION.x; }

        return (keys::KeyHeldDown(increaseKey) || keys::KeyHeldDown(decreaseKey));
    }

    auto Update(Camera &camera) -> void {
        camera.AddTargetX(MOVE_SENSITIVIY.x * moveSpeed.x * -cosf(camera.GetThetaXZ()));
        camera.AddTargetZ(MOVE_SENSITIVIY.x * moveSpeed.x * -sinf(camera.GetThetaXZ()));

        camera.AddTargetX(MOVE_SENSITIVIY.y * moveSpeed.y * sinf(camera.GetThetaXZ()));
        camera.AddTargetZ(MOVE_SENSITIVIY.y * moveSpeed.y * -cosf(camera.GetThetaXZ()));

        const bool moveSpeedUpdatedX = UpdateMoveSpeed(GLFW_KEY_W, GLFW_KEY_S, moveSpeed.x);
        const bool moveSpeedUpdatedZ = UpdateMoveSpeed(GLFW_KEY_D, GLFW_KEY_A, moveSpeed.y);

        if (!moveSpeedUpdatedX) { CheckLowerBounds(moveSpeed.x); }
        if (!moveSpeedUpdatedZ) { CheckLowerBounds(moveSpeed.y); }

        CheckUpperBounds(moveSpeed.x);
        CheckUpperBounds(moveSpeed.y);
    }
}