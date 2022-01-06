#pragma once

#include "CameraSettings.h"
#include "Window/window.h"
#include "glm/glm.hpp"



class Camera {
private:
    static const double PI;
    static const glm::vec3 VERTICAL;

    const CameraSettings settings_;

    glm::vec3 back_;
    glm::vec3 up_;
    glm::vec3 right_;

    float zoom_;
    float thetaXZ_;
    float thetaXY_;

    glm::vec3 position_;
    glm::vec3 target_;

    glm::mat4 view_;
    const glm::mat4 projection_;

    auto CheckThetaBounds() -> void;
    auto CheckZoomBounds() -> void;
    auto UpdatePosition() -> void;
    auto UpdateDirection() -> void;

public:
    Camera(const CameraSettings &cameraSettings);

    auto GetView() -> glm::mat4;
    auto GetProjection() -> glm::mat4;

    auto SetTarget(float x, float y, float z) -> void;
    [[nodiscard]] auto GetTarget() const -> glm::vec3;
    auto AddTargetX(float deltaX) -> void;
    auto AddTargetY(float deltaY) -> void;
	auto AddTargetZ(float deltaZ) -> void;

    auto Zoom(float deltaZoom) -> void;
    auto AddThetaXZ(float deltaThetaXZ) -> void;
    auto AddThetaXY(float deltaThetaXY) -> void;
    [[nodiscard]] auto GetThetaXZ() const -> float;

    auto Update() -> void;
};