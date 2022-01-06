#include "debug.h"

#include "Geometry/Geometry.h"
#include "Input/keys.h"



namespace debug {
    namespace {
        bool wireframeMode;
    }

    auto ToggleWireframeMode() -> void{
        wireframeMode = !wireframeMode;
        if (wireframeMode) { Geometry::EnableWireframeMode(); }
        else               { Geometry::DisableWireframeMode(); }
    }

    auto CheckToggleWireframeKey() -> void {
        keys::BindFunctionToKeyPress(GLFW_KEY_F1, ToggleWireframeMode);
    }

    auto Update() -> void {
        CheckToggleWireframeKey();
    }
}