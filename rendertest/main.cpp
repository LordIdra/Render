#include <vector>
#include <iostream>
#include <array>

#include "Core/Core.h"
#include "Input/Mouse.h"
#include "Input/Keys.h"
#include "Window/Window.h"

#include "Debug.h"
#include "Move.h"
#include "Render.h"
#include "Zoom.h"



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

TerrainStorage terrainStorage;



void GenerateChunks() {
    terrainStorage.GenerateChunk(0, 0);
    terrainStorage.GenerateChunk(0, 1);
    terrainStorage.GenerateChunk(1, 0);
    terrainStorage.GenerateChunk(1, 1);
    terrainStorage.GenerateChunk(0, -1);
    terrainStorage.GenerateChunk(-1, 0);
    terrainStorage.GenerateChunk(-1, -1);
    terrainStorage.GenerateChunk(-1, 1);
    terrainStorage.GenerateChunk(0, 2);
    terrainStorage.GenerateChunk(-2, 0);
}

void CreateMap() {
    terrainStorage = TerrainStorage();
    GenerateChunks();
}

void CheckWindowCloseKey() {
    if (Keys::KeyHeldDown(GLFW_KEY_ESCAPE)) Window::SetShouldClose();
}

void Mainloop() {
    while (!Window::ShouldClose()) {
        Render::Update(terrainStorage, chunkCoordinates);
        Core::Update();
        Move::Update();
        Zoom::Update();
        Debug::Update();
        CheckWindowCloseKey();
    }
    Window::Terminate();
}

int main() {
    Core::Initialize();
    CreateMap();
    Camera::SetTarget(0.0f, 0.0f, 0.0f);
    Camera::SetMinZoom(5.0f);
    Camera::SetMaxZoom(50.0f);
    Mouse::Hide();
    Render::Initialize();
    Mainloop();
}