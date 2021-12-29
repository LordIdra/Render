#include "Camera/Camera.h"

#include "Window/Window.h"
#include "glm/gtc/matrix_transform.hpp"



namespace Camera {
    namespace Detail {
        const double PI = 3.1416;
        const glm::vec3 VERTICAL = glm::vec3(0.0f, 1.0f, 0.0f);

        double maxThetaXY = PI / 2.2;
        float fieldOfView = 45.0f;
        float near = 0.1f;
        float far = 100.0f;

        double minZoom = 1.0f;
        double maxZoom = 20.0f;

        glm::vec3 back = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::vec3(0.0f, 0.0f, 1.0f);

        float zoom = 10.0f;
        float thetaXZ = 0.0f;
        float thetaXY = 0.0f;

        glm::vec3 position;
        glm::vec3 target;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        void CheckThetaBounds() {
            if (thetaXY > maxThetaXY)  thetaXY = maxThetaXY;
            if (thetaXY < -maxThetaXY) thetaXY = -maxThetaXY;
        }

        void CheckZoomBounds() {
            if (zoom > maxZoom) zoom = maxZoom;
            if (zoom < minZoom) zoom = minZoom;
        }

        void UpdatePosition() {
            position.x = target.x + (zoom * cos(thetaXZ));
            position.z = target.z + (zoom * sin(thetaXZ));

            position.y = target.y + (zoom * sin(thetaXY));
            position.x = target.x + (zoom * cos(thetaXZ) * cos(thetaXY));
            position.z = target.z + (zoom * sin(thetaXZ) * cos(thetaXY));
        }

        void UpdateDirection() {
            back = glm::normalize(position - target);
            right = glm::normalize(glm::cross(VERTICAL, back));
            up = glm::cross(back, right);
            view = glm::lookAt(position, target, VERTICAL);
        }
    }



    void Initialize() {
        Detail::projection = glm::perspective(glm::radians(Detail::fieldOfView), ((float)Window::GetWidth()) / ((float)Window::GetHeight()), Detail::near, Detail::far);
    }
    
    glm::mat4 GetView() {
        return Detail::view;
    }

    glm::mat4 GetProjection() {
        return Detail::projection;
    }

    void SetTarget(float x, float y, float z) {
        Detail::target = glm::vec3(x, y, z);
    }

    void SetMinZoom(float min) {
        Detail::minZoom = min;
    }
    void SetMaxZoom(float max) {
        Detail::maxZoom = max;
    }

    void SetMaxThetaXY(float theta) {
        Detail::maxThetaXY = theta;
    }

    float GetThetaXZ() {
        return Detail::thetaXZ;
    }

    void SetNear(float near) {
        Detail::near = near;
    }

    void SetFar(float far) {
        Detail::far = far;
    }

    void AddTargetX(float deltaX) {
        Detail::target.x += deltaX;
    }

    void AddTargetY(float deltaY) {
        Detail::target.y += deltaY;
    }

    void AddTargetZ(float deltaZ) {
        Detail::target.z += deltaZ;
    }

    void Zoom(double deltaZoom) {
        Detail::zoom *= 1 - deltaZoom;
        Detail::CheckZoomBounds();
    }
    
    void AddThetaXZ(float deltaThetaXZ) {
        Detail::thetaXZ += deltaThetaXZ;
    }
    
    void AddThetaXY(float deltaThetaXY) {
        Detail::thetaXY += deltaThetaXY;
        Detail::CheckThetaBounds();
    }
    
    void Update() {
        Detail::UpdatePosition();
        Detail::UpdateDirection();
    }
}