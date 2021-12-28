#include <vector>
#include <iostream>
#include <array>

#include "Camera/Camera.h"
#include "Core/Core.h"
#include "Geometry/Geometry.h"
#include "Input/Mouse.h"
#include "Input/Keys.h"
#include "Logging/Logging.h"
#include "Shaders/Program.h"
#include "Window/Window.h"

#include "Map.h"
#include "Indices.h"



Program program;

std::vector<std::array<int, 2>> chunkCoordinates = {
    std::array<int, 2> {0, 0},
    std::array<int, 2> {0, 1},
    std::array<int, 2> {1, 0},
    std::array<int, 2> {1, 1},
    std::array<int, 2> {0, -1},
    std::array<int, 2> {-1, 0},
    std::array<int, 2> {-1, -1},
    std::array<int, 2> {-1, 1},
    std::array<int, 2> {0, 2},
    std::array<int, 2> {-2, 0}
};

std::vector<Vertex> vertices;
std::vector<unsigned int> indices;

const float MOVE_SENSITIVIY = 0.08f;
const float MOVE_DECCELERATION = 0.12f;

const float ZOOM_SENSITIVIY = 0.08f;
const float ZOOM_DECCELERATION = 0.12f;

float zoom_speed = 0.0f;

Map map;



void GenerateChunks() {
    map.GenerateChunk(0, 0);
    map.GenerateChunk(0, 1);
    map.GenerateChunk(1, 0);
    map.GenerateChunk(1, 1);
    map.GenerateChunk(0, -1);
    map.GenerateChunk(-1, 0);
    map.GenerateChunk(-1, -1);
    map.GenerateChunk(-1, 1);
    map.GenerateChunk(0, 2);
    map.GenerateChunk(-2, 0);
}

void DrawChunks() {
    vertices = map.GetAllVertices(chunkCoordinates);
    indices = Indices::GetAllIndices(map, chunkCoordinates);
}

void CreateMap() {
    map = Map();
    GenerateChunks();
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

void UpdateMove() {
    
}

void UpdateZoom() {
    Camera::AddThetaXZ(Mouse::positionDelta.x); 
    Camera::AddThetaXY(Mouse::positionDelta.y);
    if (Mouse::scrollDelta.y != 0) {
        zoom_speed = Mouse::scrollDelta.y;
    } else {
        if      (zoom_speed >  (ZOOM_DECCELERATION/2.0f)) zoom_speed -= ZOOM_DECCELERATION;
        else if (zoom_speed < -(ZOOM_DECCELERATION/2.0f)) zoom_speed += ZOOM_DECCELERATION;
        else                          zoom_speed = 0;
    }
    Camera::Zoom(zoom_speed * ZOOM_SENSITIVIY);
}

void UpdateCamera() {
    UpdateMove();
    UpdateZoom();
}

void Render() {
    glm::mat4 projection = Camera::GetProjection();
    glm::mat4 view = Camera::GetView();
    program.Use();
    program.Set("projection", projection);
    program.Set("view", view);
    DrawChunks();
    Geometry::SetVertices(vertices);
    Geometry::SetIndices(indices);
}

void Mainloop() {
    while (!Window::ShouldClose()) {
        Render();
        HandleInput();
        Core::Update();
        UpdateCamera();
    }
    Window::Terminate();
}

int main() {
    Core::Initialize();
    CreateMap();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Camera::SetTarget(0.0f, 0.0f, 0.0f);
    Camera::SetMinZoom(5.0f);
    Camera::SetMaxZoom(50.0f);
    Mouse::Hide();
    CreateProgram();
    Mainloop();
}