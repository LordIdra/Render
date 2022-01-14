#include <cstdio>
#include <vector>
#include <iostream>
#include <array>

#include "mouse.h"
#include "keys.h"

#include "logging.h"
#include "TerrainStorage.h"
#include "terrain_generator.h"
#include "visualdebug.h"
#include "move.h"
#include "zoom.h"
#include "Visualiser.h"
#include "init.h"



const int VIEW_DISTANCE = 9;



void GenerateChunks(TerrainStorage &terrainStorage, const std::vector<ChunkCoord> &chunks) {
    for (const ChunkCoord chunk : chunks) {
        terrainStorage.GenerateChunk(chunk);
    }
}

void CheckWindowCloseKey() {
    if (keys::KeyHeldDown(GLFW_KEY_ESCAPE)) { window::SetShouldClose(); }
}

void Mainloop(TerrainStorage &terrainStorage, Camera &camera, Visualiser &visualiser) {
    while (!window::ShouldClose()) {
        const WorldCoord target = camera.GetTarget();
        move::Update(camera);
        zoom::Update(camera);
        mouse::Update();
        visualdebug::Update();
        terrainStorage.GenerateChunksInRadius(target, VIEW_DISTANCE);   // we use target.z here since it's 3 a dimensional vector
        visualiser.Update(TerrainStorage::GetChunkCoordinatesInRadius(target, VIEW_DISTANCE));
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
        .far = 200.0,
        .minZoom = 5.0,
        .maxZoom = 50.0
    };
    Camera camera(cameraSettings);
    TerrainStorage terrainStorage;
    terrain_generator::Initialize(1);
    camera.SetTarget(0.0, 0.0, 0.0);
    mouse::Hide();
    Visualiser visualiser(&camera, &terrainStorage);
    Mainloop(terrainStorage, camera, visualiser);
}