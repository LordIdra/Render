#include "Window/Window.h"

#include "Logging/Logging.h"



namespace Window {

    GLFWmonitor *Detail::monitor;
    GLFWwindow *Detail::window;
    const GLFWvidmode *Detail::mode;

    namespace Detail {
        
        int width;
        int height;
        int deltaTime = 0;

        void SetVersionHints() {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        void AcquireMonitor() {
            monitor = glfwGetPrimaryMonitor();
            mode = glfwGetVideoMode(monitor);
        }

        void SetColorHints() {
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        }

        void SetRenderHints() {
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            glfwWindowHint(GLFW_SAMPLES, SAMPLES);
        }

        void CreateWindow() {
            window = glfwCreateWindow(mode->width, mode->height, NAME.c_str(), monitor, NULL);
            if (window == NULL) {
                Logging::Info("Failed to initialize window");
                glfwTerminate();
                return;
            }
        }

        void AcquireWindowParameters() {
            width = mode->width;
            height = mode->height;
            glfwMakeContextCurrent(window);
        }

        void InitializeGlfw() {
            if (!glfwInit()) {
                Logging::Info("Failed to initialize GLFW.");
                return;
            }
            SetVersionHints();
            AcquireMonitor();
        }

        void InitializeGlad() {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                Logging::Info("Failed to initialize GLAD.");
                return;
            }
            glEnable(GL_DEPTH_TEST);
        }

        void InitializeHints() {
            SetColorHints();
            SetRenderHints();
        }

        void InitializeWindow() {
            CreateWindow();
            AcquireWindowParameters();
            glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        }
    }

    void Initialize() {
        Detail::InitializeGlfw();
        Detail::InitializeHints();
        Detail::InitializeWindow();
        Detail::InitializeGlad();   
    }

    GLFWwindow* GetWindow() {
        return Detail::window;   
    }

    int GetWidth() {
        return Detail::width;
    }

    int GetHeight() {
        return Detail::height;
    }

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Background(const float r, const float g, const float b, const float a) {
        glClearColor(r, g, b, a);
    }

    void SwapBuffers() {
        glfwSwapBuffers(Detail::window);
    }

    void PollEvents() {
        glfwPollEvents();
    }

    void UpdateTime() {
        Detail::deltaTime = glfwGetTime() - Detail::deltaTime;
    }

    bool ShouldClose() {
        return glfwWindowShouldClose(Detail::window);
    }

    void SetShouldClose() {
        glfwSetWindowShouldClose(Detail::window, true);
    }

    void Terminate() {
        glfwTerminate();
    }
}