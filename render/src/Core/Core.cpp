#include "Core/Core.h"

#include "Geometry/Geometry.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Input/Keys.h"
#include "Input/Mouse.h"



namespace Core {
    void Initialize() {
        Window::Initialize();
        Mouse::Initialize();
        Keys::Initialize();
        Camera::Initialize();
        Geometry::Initialize();
    }

    void Update() {
        Mouse::Reset();
        Camera::Update();
        Geometry::Update();
        Window::SwapBuffers();
        Window::Clear();
        Window::UpdateTime();
        Window::PollEvents();
    }
}