#include "Camera/Camera.h"

#include <iostream>
#include "glm/gtc/matrix_transform.hpp"



/* PRIVATE ------------------- */
const double Camera::PI = 3.1416;
const glm::vec3 Camera::VERTICAL = glm::vec3(0.0, 1.0, 0.0);

auto Camera::CheckThetaBounds() -> void {
    if (thetaXY_ > settings_.maxThetaXY)  { thetaXY_ = settings_.maxThetaXY; }
    if (thetaXY_ < -settings_.maxThetaXY) { thetaXY_ = -settings_.maxThetaXY; }
}

auto Camera::CheckZoomBounds() -> void {
    if (zoom_ > settings_.maxZoom) { zoom_ = settings_.maxZoom; }
    if (zoom_ < settings_.minZoom) { zoom_ = settings_.minZoom; }
}

auto Camera::UpdatePosition() -> void {
    position_.x = target_.x + (zoom_ * cosf(thetaXZ_));
    position_.z = target_.z + (zoom_ * sinf(thetaXZ_));

    position_.y = target_.y + (zoom_ * sinf(thetaXY_));
    position_.x = target_.x + (zoom_ * cosf(thetaXZ_) * cosf(thetaXY_));
    position_.z = target_.z + (zoom_ * sinf(thetaXZ_) * cosf(thetaXY_));
}

auto Camera::UpdateDirection() -> void {
    back_ = glm::normalize(position_ - target_);
    right_ = glm::normalize(glm::cross(VERTICAL, back_));
    up_ = glm::cross(back_, right_);
    view_ = glm::lookAt(position_, target_, VERTICAL);
}



/* PUBLIC -------------------- */
Camera::Camera(const CameraSettings &cameraSettings) 
    : settings_(cameraSettings),
      back_(glm::vec3(-1.0, 0.0, 0.0)),
      up_(glm::vec3(0.0, 1.0, 0.0)),
      right_(glm::vec3(0.0, 0.0, 1.0)),
      zoom_(0.0), 
      thetaXZ_(0.0), 
      thetaXY_(0.0),
      position_(glm::vec3(0.0)),
      target_(glm::vec3(0.0)),
      view_(glm::mat4(1.0)),
      projection_(glm::perspective(
        settings_.fieldOfView, 
        ((float)window::GetWidth()) / ((float)window::GetHeight()), 
        settings_.near, settings_.far)) {}
    
auto Camera::GetView() -> glm::mat4 {
    return view_;
}

auto Camera::GetProjection() -> glm::mat4 {
    return projection_;
}
auto Camera::SetTarget(float x, float y, float z) -> void {
    target_ = glm::vec3(x, y, z);
}

auto Camera::GetTarget() const -> glm::vec3 {
    return target_;
}

auto Camera::AddTargetX(float deltaX) -> void {
    target_.x += deltaX;
}

auto Camera::AddTargetY(float deltaY) -> void {
    target_.y += deltaY;
}

auto Camera::AddTargetZ(float deltaZ) -> void {
    target_.z += deltaZ;
}

auto Camera::Zoom(float deltaZoom) -> void {
    zoom_ *= 1.0F - deltaZoom;
    CheckZoomBounds();
}

auto Camera::AddThetaXZ(float deltaThetaXZ) -> void {
    thetaXZ_ += deltaThetaXZ;
}

auto Camera::AddThetaXY(float deltaThetaXY) -> void {
    thetaXY_ += deltaThetaXY;
    CheckThetaBounds();
}

auto Camera::GetThetaXZ() const -> float {
    return thetaXZ_;
}

auto Camera::Update() -> void {
    UpdatePosition();
    UpdateDirection();
}