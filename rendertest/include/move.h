#pragma once

#include "Camera/Camera.h"



namespace move {
    auto CheckLowerBounds(float &moveSpeedDirection, float accel) -> void;
    auto CheckUpperBounds(float &moveSpeedDirection, float maxSpeed) -> void;

    auto UpdateMoveSpeed(int increaseKey, int decreaseKey, float &moveSpeedDirection, float accel) -> bool;
    auto Update(Camera &camera) -> void;
}