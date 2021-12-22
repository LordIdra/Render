#include "Camera.h"

#include "../../include/glm/gtc/matrix_transform.hpp"



const glm::vec3 Camera::Detail::vertical = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Camera::Detail::back = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 Camera::Detail::up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Camera::Detail::right = glm::vec3(0.0f, 0.0f, 1.0f);



void Camera::Detail::UpdateDirection() {
    back = glm::normalize(position - target);
    right = glm::cross(vertical, back);
    up = glm::cross(back, right);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
  		        glm::vec3(0.0f, 0.0f, 0.0f), 
  		        glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetPosition(float x, float y, float z) {
    Detail::position = glm::vec3(x, y, z);
}

void Camera::SetTarget(float x, float y, float z) {
    Detail::target = glm::vec3(x, y, z);
}