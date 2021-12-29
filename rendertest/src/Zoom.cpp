#include "Zoom.h"

#include "Camera/Camera.h"
#include "Input/Mouse.h"


namespace Zoom {
    namespace Detail {
        const float MOUSE_SENSITIVIY = 6.0f;
        const float ZOOM_SENSITIVIY = 0.1f;
        const float ZOOM_ACCELERATION = 0.12f;

        float zoomSpeed = 0.0f;
    }

    void Update() {
        Camera::AddThetaXZ(Detail::MOUSE_SENSITIVIY * Mouse::positionDelta.x);
        Camera::AddThetaXY(Detail::MOUSE_SENSITIVIY * Mouse::positionDelta.y);

        if      (Mouse::scrollDelta.y != 0)             Detail::zoomSpeed = Mouse::scrollDelta.y;
        else if (Detail::zoomSpeed >  (Detail::ZOOM_ACCELERATION/2.0f)) Detail::zoomSpeed -= Detail::ZOOM_ACCELERATION;
        else if (Detail::zoomSpeed < -(Detail::ZOOM_ACCELERATION/2.0f)) Detail::zoomSpeed += Detail::ZOOM_ACCELERATION;
        else                                            Detail::zoomSpeed = 0;

        Camera::Zoom(Detail::zoomSpeed * Detail::ZOOM_SENSITIVIY);
    }
}