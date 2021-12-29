#include "Debug.h"

#include "Geometry/Geometry.h"
#include "Input/Keys.h"



namespace Debug {
    namespace Detail {
        bool wireframeMode;
    }

    void ToggleWireframeMode() {
        Detail::wireframeMode = !Detail::wireframeMode;
        if (Detail::wireframeMode)  Geometry::EnableWireframeMode();
        else                        Geometry::DisableWireframeMode();
    }

    void CheckToggleWireframeKey() {
        Keys::BindFunctionToKeyPress(GLFW_KEY_F1, ToggleWireframeMode);
    }

    void Update() {
        CheckToggleWireframeKey();
    }
}