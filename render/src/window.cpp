#include "window.h"

#include "logging.h"
#include <GLFW/glfw3.h>



namespace window {
    namespace {
        GLFWmonitor *monitor_;
        GLFWwindow *window_;
        const GLFWvidmode *mode_;

        int width_;
        int height_;
        float deltaTime_;

        auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void {
            glViewport(0, 0, width, height);
        }

        auto AcquireMonitorAndMode() -> void {
            monitor_ = glfwGetPrimaryMonitor();
            mode_ = glfwGetVideoMode(monitor_);
            width_ = mode_->width;
            height_ = mode_->height;
        }

        void SetWindowHints() {
            glfwWindowHint(GLFW_RED_BITS, mode_->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode_->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode_->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode_->refreshRate);
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // this prevents flashing when the window is initially created
        }

        auto CheckWindowCreated() -> void {
            if (window_ == nullptr) {
                logging::Error("Failed to initialize window");
                glfwTerminate();
                return;
            }
        }

        auto CreateWindow(const std::string &name) -> void {
            window_ = glfwCreateWindow(mode_->width, mode_->height, name.c_str(), monitor_, nullptr);
            glfwMakeContextCurrent(window_);
            glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
        }

        auto UpdateTime() -> void {
            deltaTime_ = (float)glfwGetTime() - deltaTime_;
        }

        auto SwapBuffers() -> void {
            glfwSwapBuffers(window_);
        }

        auto PollEvents() -> void {
            glfwPollEvents();
        }

        auto Clear() -> void {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }

    auto Initialize(const std::string &name) -> void {
        AcquireMonitorAndMode();
        SetWindowHints();
        CreateWindow(name);
    }

    auto GetWindow() -> GLFWwindow* {
        return window_;
    }

    auto GetWidth() -> int {
        return width_;
    }

    auto GetHeight() -> int {
        return height_;
    }

    auto Update() -> void {
        UpdateTime();
        SwapBuffers();
        PollEvents();
        Clear();
    }

    auto ShouldClose() -> bool {
        return glfwWindowShouldClose(window_);
    }

    auto SetShouldClose()-> void {
        glfwSetWindowShouldClose(window_, true);
    }
}