#pragma once

#include "glm/glm.hpp"



struct CameraSettings {
    const float maxThetaXY;
    const float fieldOfView;
    const float near;
    const float far;
    const float minZoom;
    const float maxZoom;
};