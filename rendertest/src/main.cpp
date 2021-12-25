#include <vector>
#include <iostream>
#include "Camera/Camera.h"
#include "Core/Core.h"
#include "Geometry/Geometry.h"
#include "Input/Mouse.h"
#include "Input/Keys.h"
#include "Shaders/Program.h"
#include "Window/Window.h"



Program program;

std::vector<Vertex> vertices = {
    Vertex{position: glm::vec3( 0.5f,  0.5f,  0.5f), color: glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
    Vertex{position: glm::vec3( 0.5f,  0.5f, -0.5f), color: glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},
    Vertex{position: glm::vec3( 0.5f, -0.5f,  0.5f), color: glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},
    Vertex{position: glm::vec3( 0.5f, -0.5f, -0.5f), color: glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},

    Vertex{position: glm::vec3(-0.5f,  0.5f,  0.5f), color: glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
    Vertex{position: glm::vec3(-0.5f,  0.5f, -0.5f), color: glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)},
    Vertex{position: glm::vec3(-0.5f, -0.5f,  0.5f), color: glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)},
    Vertex{position: glm::vec3(-0.5f, -0.5f, -0.5f), color: glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}
};

std::vector<unsigned int> indices {
    0, 1, 2,
    1, 2, 3,
    4, 5, 6,
    5, 6, 7
};

const float ZOOM_SENSITIVIY = 0.2;



void CreateTriangle() {
    Geometry::SetVertices(vertices);
    Geometry::SetIndices(indices);
}

void CreateProgram() {
    Shader vertex("../../rendertest/resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragment("../../rendertest/resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    program.Init();
    program.AddShader(vertex);
    program.AddShader(fragment);
    program.Link();
}

void HandleInput() {
    if (Keys::KeyDown(GLFW_KEY_ESCAPE)) Window::SetShouldClose();
}

void UpdateCamera() {
    Camera::AddThetaXZ(Mouse::positionDelta.x); 
    Camera::AddThetaXY(Mouse::positionDelta.y);
    Camera::Zoom(Mouse::scrollDelta.y * ZOOM_SENSITIVIY);
}

void Draw() {
    glm::mat4 projection = Camera::GetProjection();
    glm::mat4 view = Camera::GetView();
    program.Use();
    program.Set("projection", projection);
    program.Set("view", view);
}

void Mainloop() {
    while (!Window::ShouldClose()) {
        Draw();
        HandleInput();
        Core::Update();
        UpdateCamera();
    }
    Window::Terminate();
}

int main() {
    Core::Initialize();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Camera::SetTarget(2.0f, 0.0f, 0.0f);
    Mouse::Hide();
    CreateProgram();
    CreateTriangle();
    Mainloop();
}