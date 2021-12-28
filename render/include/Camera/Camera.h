#pragma once

#include "glm/glm.hpp"



namespace Camera {
    namespace Detail {
        extern const double PI;
        extern const double MAX_THETA_XY;
        extern const double ZOOM_SENSITIVITY;
        
        extern const double FIELD_OF_VIEW;

        extern const glm::vec3 VERTICAL;

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
    void SetMaxZoom(float min);

    void Zoom(double deltaZoom);
    void AddThetaXZ(float deltaThetaXZ);
    void AddThetaXY(float deltaThetaXY);

    void Update();
}