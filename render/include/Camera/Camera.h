#pragma once

#include "glm/glm.hpp"
#include "CameraSettings.h"



class Camera {
private:
    static const double PI;
    static const glm::vec3 VERTICAL;

    const CameraSettings settings;

    glm::vec3 back;
    glm::vec3 up;
    glm::vec3 right;

    float zoom;
    float thetaXZ;
    float thetaXY;

    glm::vec3 position;
    glm::vec3 target;

    glm::mat4 view;
    glm::mat4 projection;

    void CheckThetaBounds();
    void CheckZoomBounds();
    void UpdatePosition();
    void UpdateDirection();



public:
    Camera(CameraSettings &cameraSettings);

    glm::mat4 GetView();
    glm::mat4 GetProjection();

    void SetTarget(float x, float y, float z);
    void SetMinZoom(float min);
    void SetMaxZoom(float max);
    void SetMaxThetaXY(float theta);
    void SetNear(float near);
    void SetFar(float far);

    void AddTargetX(float deltaX);
    void AddTargetY(float deltaY);
    void AddTargetZ(float deltaZ);

    void Zoom(double deltaZoom);
    void AddThetaXZ(float deltaThetaXZ);
    void AddThetaXY(float deltaThetaXY);
    float GetThetaXZ();

    void Update();
};