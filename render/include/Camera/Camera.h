#pragma once

#include "glm/glm.hpp"



namespace Camera {
    namespace Detail {
        extern const double PI;
        extern const glm::vec3 VERTICAL;

        extern double maxThetaXY;
        extern float fieldOfView;
        extern float near;
        extern float far;

        extern double minZoom;
        extern double maxZoom;

        extern glm::vec3 back;
        extern glm::vec3 up;
        extern glm::vec3 right;

        extern float zoom;
        extern float thetaXZ;
        extern float thetaXY;

        extern glm::vec3 position;
        extern glm::vec3 target;

        extern glm::mat4 view;
        extern glm::mat4 projection;

        void CheckThetaBounds();
        void CheckZoomBounds();
        void UpdatePosition();
        void UpdateDirection();
    }
    
    void Initialize();

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

    void Update();
}