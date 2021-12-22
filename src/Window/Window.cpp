#include "Window.h"

#include "../Logging/Logging.h"
#include "../Input/Mouse/Mouse.h"
#include "../Input/Keys/Keys.h"



GLFWmonitor *Window::Detail::monitor;
GLFWwindow *Window::Detail::window;
const GLFWvidmode *Window::Detail::mode;

int Window::Detail::width;
int Window::Detail::height;
int Window::Detail::deltaTime = 0;



void Window::Detail::SetVersionHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::Detail::AcquireMonitor() {
    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
}

void Window::Detail::SetColorHints() {
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
}

void Window::Detail::SetRenderHints() {
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_SAMPLES, SAMPLES);
}

void Window::Detail::CreateWindow() {
    window = glfwCreateWindow(mode->width, mode->height, NAME.c_str(), monitor, NULL);
    if (window == NULL) {
        Logging::Info("Failed to initialize window");
        glfwTerminate();
        return;
    }
}

void Window::Detail::AcquireWindowParameters() {
    width = mode->width;
    height = mode->height;
    glfwMakeContextCurrent(window);
    Mouse::SetWindow(window);
    Keys::SetWindow(window);
}

void Window::Detail::InitializeGlfw() {
    if (!glfwInit()) {
        Logging::Info("Failed to initialize GLFW.");
        return;
    }
    SetVersionHints();
    AcquireMonitor();
}

void Window::Detail::InitializeGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logging::Info("Failed to initialize GLAD.");
        return;
    }
    glEnable(GL_DEPTH_TEST);
}

void Window::Detail::InitializeHints() {
    SetColorHints();
    SetRenderHints();
}

void Window::Detail::InitializeWindow() {
    CreateWindow();
    AcquireWindowParameters();
}

void Window::Initialize() {
    Detail::InitializeGlfw();
    Detail::InitializeHints();
    Detail::InitializeWindow();
    Detail::InitializeGlad();   
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Background(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(Detail::window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::UpdateTime() {
    Detail::deltaTime = glfwGetTime() - Detail::deltaTime;
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(Detail::window);
}

void Window::SetShouldClose() {
    glfwSetWindowShouldClose(Detail::window, true);
}

void Window::Terminate() {
    glfwTerminate();
}

void Window::UpdateMouse() {
    Mouse::Update();
}
