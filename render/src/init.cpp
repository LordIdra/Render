#include "init.h"

#include "logging.h"
#include "keys.h"
#include "mouse.h"
#include "window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"



namespace init {
    namespace {
        const int MAJOR_VERSION_ = 3;
        const int MINOR_VERSION_ = 3;

        auto ErrorCallback(int error, const char* description) -> void {
            logging::Error(description);
        }
        
        auto SetVersionHints() -> void {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION_);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION_);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        auto InitializeGlfw() -> void {
            if (!glfwInit()) {
                logging::Error("Failed to initialize GLFW.");
                return;
            }
            SetVersionHints();
        }

        auto InitializeGlad() -> void {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {  //NOLINT - required cast for GLAD initialization
                logging::Error("Failed to initialize GLAD.");
                return;
            }
            glEnable(GL_DEPTH_TEST);
        }

        auto TerminateGlfw() -> void {
            glfwTerminate();
        }
    }

    auto Initialize(const std::string &windowName) -> void {
        InitializeGlfw();
        window::Initialize(windowName);
        InitializeGlad();
        keys::Initialize();
        mouse::Initialize();
    }

    auto Terminate() -> void {
        TerminateGlfw();
    }
}