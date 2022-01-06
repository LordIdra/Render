#include "zoom.h"

#include "Input/mouse.h"
#include <iostream>

namespace zoom {
    namespace {
        const float MOUSE_SENSITIVIY = 6.0;
        const float ZOOM_ACCELERATION = 0.14;
        const float ZOOM_DECCELERATION = 0.02;

        float zoomSpeed = 0.0;
    }

    void Update(Camera &camera) {
        camera.AddThetaXZ(MOUSE_SENSITIVIY * mouse::GetPositionDelta().x);
        camera.AddThetaXY(MOUSE_SENSITIVIY * mouse::GetPositionDelta().y);

        const float THRESHOLD_DIVISOR = 2.0;
        if      (mouse::GetScrollDelta().y != 0)                        { zoomSpeed = mouse::GetScrollDelta().y * ZOOM_ACCELERATION; }
        else if (zoomSpeed >  (ZOOM_DECCELERATION/THRESHOLD_DIVISOR))   { zoomSpeed -= ZOOM_DECCELERATION; }
        else if (zoomSpeed < -(ZOOM_DECCELERATION/THRESHOLD_DIVISOR))   { zoomSpeed += ZOOM_DECCELERATION; }
        else                                                            { zoomSpeed = 0; }

        camera.Zoom(zoomSpeed);
    }
}