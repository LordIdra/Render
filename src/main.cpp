#include <memory>
#include "Input/Mouse/Mouse.h"
#include "Input/Keys/Keys.h"
#include "Window/Window.h"
#include "Memory/VAO.h"
#include "Shaders/Program.h"


VAO vao;
Program program;
std::vector<float> triangleVertices = {
    0.0f, 0.5f, 0.0f,      0.5f, 0.9f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.0f,      0.5f, 0.9f, 0.0f, 1.0f,
    -0.5f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f
};



void CreateTriangle() {
    vao.Init();
    
    vao.AddVertexAttribute(VertexAttribute{
        index: 0, 
        size: 3, 
        type: GL_FLOAT, 
        normalised: GL_FALSE, 
        stride: 7 * sizeof(GL_FLOAT), 
        offset: (void*)0
    });

    vao.AddVertexAttribute(VertexAttribute{
        index: 1,
        size: 4,
        type: GL_FLOAT, 
        normalised: GL_FALSE, 
        stride: 7 * sizeof(GL_FLOAT), 
        offset: (void*)(3*sizeof(float))
    });

    vao.Data(triangleVertices);
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
    vertex.~Shader();
    fragment.~Shader();
}

void Initialize() {
    Window::Initialize();
    CreateProgram();
    CreateTriangle();
}

void HandleInput() {
    if (Keys::KeyDown(GLFW_KEY_ESCAPE)) Window::SetShouldClose();
    Window::UpdateTime();
    Window::UpdateMouse();
    Window::PollEvents();
}

void ClearWindow() {
    Window::Background(0.3, 0.3, 0.4, 1.0);
    Window::Clear();
}

void UpdateWindow() {
    Window::SwapBuffers();
}

void Mainloop() {
    Mouse::Hide();
    while (!Window::ShouldClose()) {
        HandleInput();
        ClearWindow();
        DrawTriangle();
        UpdateWindow();
    }
    Window::Terminate();
}

int main() {
    Initialize();
    Mainloop();
}