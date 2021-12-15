#include "Window/Window.h"
#include "Memory/VAO.h"
#include "Shaders/Program.h"

VAO vao;
Program program;
const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};


void CreateTriangle() {
    vao = VAO();
    vao.AddVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    vao.Data(vertices, sizeof(vertices));
}

void DrawTriangle() {
    program.Use();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CreateProgram() {
    Shader vertex("resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragment("resources/shaders/vertex.glsl", GL_FRAGMENT_SHADER);
    program = Program();
    program.AddShader(vertex);
    program.AddShader(fragment);
    program.Link();
    vertex.Delete();
    fragment.Delete();
}

void Initialize() {
    Window::Initialize();
    CreateTriangle();
}

void UpdateWindow() {
    Window::UpdateTime();
    Window::UpdateMouse();
    Window::SwapBuffers();
    Window::Clear();
    Window::Background(0.3, 0.6, 0.2, 1.0);
}

void HandleEvents() {
    Window::PollEvents();
    if (Keys::KeyDown(GLFW_KEY_ESCAPE)) Window::SetShouldClose();
}

void Mainloop() {
    Mouse::Hide();
    while (!Window::ShouldClose()) {
        UpdateWindow();
        HandleEvents();
        DrawTriangle();
    }
    Window::Terminate();
}

int main() {
    Initialize();
    Mainloop();
}