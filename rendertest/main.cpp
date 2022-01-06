#include <cstdio>
#include <vector>
#include <iostream>
#include <array>

#include "Camera/Camera.h"
#include "Camera/CameraSettings.h"
#include "Input/mouse.h"
#include "Input/keys.h"

#include "Logging/logging.h"
#include "TerrainStorage.h"
#include "debug.h"
#include "move.h"
#include "zoom.h"
#include "Visualiser.h"
#include "Init/init.h"



const int VIEW_DISTANCE = 5;



void GenerateChunks(TerrainStorage &terrainStorage, const std::vector<std::array<int, 2>> &chunks) {
    for (const std::array<int, 2> chunk : chunks) {
        terrainStorage.GenerateChunk(chunk[0], chunk[1]);
    }
}

void CheckWindowCloseKey() {
    if (keys::KeyHeldDown(GLFW_KEY_ESCAPE)) { window::SetShouldClose(); }
}

void Mainloop(TerrainStorage &terrainStorage, Camera &camera, Visualiser &visualiser) {
    while (!window::ShouldClose()) {
        const glm::vec3 TARGET = camera.GetTarget();
        move::Update(camera);
        zoom::Update(camera);
        mouse::Update();
        debug::Update();
        terrainStorage.GenerateChunksInRadius(TARGET.x, TARGET.z, VIEW_DISTANCE);   // we use target.z here since it's a vec3, not a vec2
        visualiser.Update(TerrainStorage::GetChunkCoordinatesInRadius(TARGET.x, TARGET.z, VIEW_DISTANCE));
        camera.Update();
        window::Update();
        CheckWindowCloseKey();
    }
    init::Terminate();
}

auto main() -> int {
    init::Initialize("Terrain Test");
    CameraSettings cameraSettings = {
        .maxThetaXY = 1.5,
        .fieldOfView = 0.78,
        .near = 0.1,
        .far = 100.0,
        .minZoom = 5.0,
        .maxZoom = 50.0
    };
    Camera camera(cameraSettings);
    TerrainStorage terrainStorage;
    camera.SetTarget(0.0, 0.0, 0.0);
    mouse::Hide();
    Visualiser visualiser(&camera, &terrainStorage);
    Mainloop(terrainStorage, camera, visualiser);
}