#include "Zoom.h"

#include "Camera/Camera.h"
#include "Input/Mouse.h"


namespace Zoom {

    void Update() {
        Camera::AddThetaXZ(MOUSE_SENSITIVIY * Mouse::positionDelta.x);
        Camera::AddThetaXY(MOUSE_SENSITIVIY * Mouse::positionDelta.y);

        if      (Mouse::scrollDelta.y != 0)             zoomSpeed = Mouse::scrollDelta.y;
        else if (zoomSpeed >  (ZOOM_ACCELERATION/2.0f)) zoomSpeed -= ZOOM_ACCELERATION;
        else if (zoomSpeed < -(ZOOM_ACCELERATION/2.0f)) zoomSpeed += ZOOM_ACCELERATION;
        else                                            zoomSpeed = 0;

        Camera::Zoom(zoomSpeed * ZOOM_SENSITIVIY);
    }
}