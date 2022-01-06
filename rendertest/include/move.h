#pragma once

#include "Camera/Camera.h"



namespace move {
    auto CheckLowerBounds(float &moveSpeedDirection) -> void;
    auto CheckUpperBounds(float &moveSpeedDirection) -> void;

    auto UpdateMoveSpeed(int increaseKey, int decreaseKey, float &moveSpeedDirection) -> bool;
    auto Update(Camera &camera) -> void;
}