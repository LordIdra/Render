#include <memory>
#include "Input/Keys/Keys.h"
#include "Input/Mouse/Mouse.h"
#include "Window/Window.h"
#include "Memory/VAO.h"
#include "Shaders/Program.h"



VAO vao;
Program program;
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};



void CreateTriangle() {
    vao.Init();
    vao.AddVertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    vao.Data(vertices, sizeof(vertices));
}

void DrawTriangle() {
    program.Use();
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CreateProgram() {
    Shader vertex("../resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragment("../resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    program.Init();
    program.AddShader(vertex);
    program.AddShader(fragment);
    program.Link();
    vertex.Delete();
    fragment.Delete();
}

void Initialize() {
    Window::Initialize();
    CreateProgram();
    CreateTriangle();
}

void Mainloop() {
    Mouse::Hide();
    while (!Window::ShouldClose()) {
        if (Keys::KeyDown(GLFW_KEY_ESCAPE)) Window::SetShouldClose();

        Window::Background(0.3, 0.6, 0.2, 1.0);
        Window::Clear();

        DrawTriangle();
        Window::SwapBuffers();

        Window::UpdateTime();
        Window::UpdateMouse();
        Window::PollEvents();
    }
    Window::Terminate();
}

int main() {
    Initialize();
    Mainloop();
}