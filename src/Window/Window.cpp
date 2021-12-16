#include "Window.h"



const int Window::Detail::SAMPLES = 4;
const char* Window::Detail::NAME = "Test";
const int Window::Detail::MAJOR_VERSION = 4;
const int Window::Detail::MINOR_VERSION = 4;

GLFWmonitor* Window::Detail::monitor;
GLFWwindow* Window::Detail::window;
const GLFWvidmode* Window::Detail::mode;

int Window::Detail::width;
int Window::Detail::height;
int Window::Detail::deltaTime = 0;



void Window::Detail::InitializeGlfw() {
    if (!glfwInit()) {
        Logging::Info("Failed to initialize GLFW.");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
    Logging::Info("Initialized GLFW.");
}

void Window::Detail::InitializeGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logging::Info("Failed to initialize GLAD.");
        return;
    }
    glEnable(GL_DEPTH_TEST);
    Logging::Info("Initialized GLAD.");
}

void Window::Detail::InitializeHints() {
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_SAMPLES, SAMPLES);
    Logging::Info("Initialized Hints.");
}

void Window::Detail::InitializeWindow() {
    window = glfwCreateWindow(mode->width, mode->height, NAME, monitor, NULL);
    if (window == NULL) {
        Logging::Info("Failed to initialize window");
        glfwTerminate();
        return;
    }
    width = mode->width;
    height = mode->height;
    glfwMakeContextCurrent(window);
    Mouse::SetWindow(window);
    Keys::SetWindow(window);
    Logging::Info("Initialized window.");
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

void Window::Background(float r, float g, float b, float a) {
    glClearColor(0.8, 0.0, 0.0, 1.0);
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
