#pragma once

#include "glm/glm.hpp"



struct CameraSettings {
    const double maxThetaXY;
    const float fieldOfView;
    const float near;
    const float far;
    const double minZoom;
    const double maxZoom;
};