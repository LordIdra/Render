#include "Camera/Camera.h"

#include "Window/Window.h"
#include "glm/gtc/matrix_transform.hpp"



/* STATIC VARIABLES ---------- */
const double Camera::PI = 3.1416;
const glm::vec3 Camera::VERTICAL = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 back = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 right = glm::vec3(0.0f, 0.0f, 1.0f);



/* PRIVATE ------------------- */
void Camera::CheckThetaBounds() {
    if (thetaXY > maxThetaXY)  thetaXY = maxThetaXY;
    if (thetaXY < -maxThetaXY) thetaXY = -maxThetaXY;
}

void Camera::CheckZoomBounds() {
    if (zoom > maxZoom) zoom = maxZoom;
    if (zoom < minZoom) zoom = minZoom;
}

void Camera::UpdatePosition() {
    position.x = target.x + (zoom * cos(thetaXZ));
    position.z = target.z + (zoom * sin(thetaXZ));

    position.y = target.y + (zoom * sin(thetaXY));
    position.x = target.x + (zoom * cos(thetaXZ) * cos(thetaXY));
    position.z = target.z + (zoom * sin(thetaXZ) * cos(thetaXY));
}

void Camera::UpdateDirection() {
    back = glm::normalize(position - target);
    right = glm::normalize(glm::cross(VERTICAL, back));
    up = glm::cross(back, right);
    view = glm::lookAt(position, target, VERTICAL);
}



/* PUBLIC -------------------- */
Camera::Camera(CameraSettings &cameraSettings) 
    : settings(cameraSettings),
      view(glm::mat4(1.0),
      zoom(0.0f), 
      thetaXZ(0.0), 
      thetaXY(0.0) {
    projection = glm::perspective(
        glm::radians(settings.fieldOfView), 
        ((float)Window::GetWidth()) / ((float)Window::GetHeight()), 
        settings.near, settings.far);
}
    
glm::mat4 Camera::GetView() {
    return view;
}

glm::mat4 Camera::GetProjection() {
    return projection;
}
void Camera::SetTarget(float x, float y, float z) {
    target = glm::vec3(x, y, z);
}

void Camera::AddTargetX(float deltaX) {
    target.x += deltaX;
}

void Camera::AddTargetY(float deltaY) {
    target.y += deltaY;
}

void Camera::AddTargetZ(float deltaZ) {
    target.z += deltaZ;
}

void Camera::Zoom(double deltaZoom) {
    zoom *= 1 - deltaZoom;
    CheckZoomBounds();
}

void Camera::AddThetaXZ(float deltaThetaXZ) {
    thetaXZ += deltaThetaXZ;
}

void Camera::AddThetaXY(float deltaThetaXY) {
    thetaXY += deltaThetaXY;
    CheckThetaBounds();
}

void Camera::Update() {
    UpdatePosition();
    UpdateDirection();
}