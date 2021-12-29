#pragma once



namespace Debug {
    namespace Detail {
        extern bool wireframeMode;
    }

    void ToggleWireframeMode();
    void CheckToggleWireframeKey();

    void Update();
}