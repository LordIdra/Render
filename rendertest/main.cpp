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

const float MOVE_SENSITIVIY = 0.1f;
const float MOVE_ACCELERATION = 0.5f;
const float MAX_MOVE_SPEED = 5.0f;

const float MOUSE_SENSITIVIY = 6.0f;

const float ZOOM_SENSITIVIY = 0.1f;
const float ZOOM_ACCELERATION = 0.12f;

float moveSpeedX = 0.0f;
float moveSpeedZ = 0.0f;

float zoomSpeed = 0.0f;

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

void UpdateMoveSpeedX() {
    if      (Keys::KeyDown(GLFW_KEY_W))                 moveSpeedX += MOVE_ACCELERATION;
    else if (Keys::KeyDown(GLFW_KEY_S))                 moveSpeedX -= MOVE_ACCELERATION;
    else if (moveSpeedX >  (MOVE_ACCELERATION/2.0f))    moveSpeedX -= MOVE_ACCELERATION;
    else if (moveSpeedX < -(MOVE_ACCELERATION/2.0f))    moveSpeedX += MOVE_ACCELERATION;
    else                                                moveSpeedX = 0;
}

void UpdateMoveSpeedZ() {
    if      (Keys::KeyDown(GLFW_KEY_D))                 moveSpeedZ += MOVE_ACCELERATION;
    else if (Keys::KeyDown(GLFW_KEY_A))                 moveSpeedZ -= MOVE_ACCELERATION;
    else if (moveSpeedZ >  (MOVE_ACCELERATION/2.0f))    moveSpeedZ -= MOVE_ACCELERATION;
    else if (moveSpeedZ < -(MOVE_ACCELERATION/2.0f))    moveSpeedZ += MOVE_ACCELERATION;
    else                                                moveSpeedZ = 0;
}

void CheckBoundsMoveSpeedX() {
    if      (moveSpeedX >  (MAX_MOVE_SPEED))            moveSpeedX = MAX_MOVE_SPEED;
    else if (moveSpeedX < -(MAX_MOVE_SPEED))            moveSpeedX = -MAX_MOVE_SPEED;
}

void CheckBoundsMoveSpeedZ() {
    if      (moveSpeedZ >  (MAX_MOVE_SPEED))            moveSpeedZ = MAX_MOVE_SPEED;
    else if (moveSpeedZ < -(MAX_MOVE_SPEED))            moveSpeedZ = -MAX_MOVE_SPEED;
}

void UpdateMove() {
    Camera::AddTargetX(MOVE_SENSITIVIY * moveSpeedX);
    Camera::AddTargetZ(MOVE_SENSITIVIY * moveSpeedZ);

    UpdateMoveSpeedX();
    UpdateMoveSpeedZ();
    
    CheckBoundsMoveSpeedX();
    CheckBoundsMoveSpeedZ();
}

void UpdateZoom() {
    Camera::AddThetaXZ(MOUSE_SENSITIVIY * Mouse::positionDelta.x);
    Camera::AddThetaXY(MOUSE_SENSITIVIY * Mouse::positionDelta.y);

    if      (Mouse::scrollDelta.y != 0)             zoomSpeed = Mouse::scrollDelta.y;
    else if (zoomSpeed >  (ZOOM_ACCELERATION/2.0f)) zoomSpeed -= ZOOM_ACCELERATION;
    else if (zoomSpeed < -(ZOOM_ACCELERATION/2.0f)) zoomSpeed += ZOOM_ACCELERATION;
    else                                            zoomSpeed = 0;

    Camera::Zoom(zoomSpeed * ZOOM_SENSITIVIY);
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