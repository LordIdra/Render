#pragma once

#include "Camera/Camera.h"



namespace move {
    auto CheckLowerBounds(float &moveSpeedDirection, float acceleration) -> void;
    auto CheckUpperBounds(float &moveSpeedDirection, float maxSpeed) -> void;

    auto UpdateMoveSpeed(int increaseKey, int decreaseKey, float &moveSpeedDirection, float acceleration) -> bool;
    auto Update(Camera &camera) -> void;
}