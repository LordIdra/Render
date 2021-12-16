cmake_minimum_required(VERSION 3.0.0)
project(Render)

set(src_files
    "src/main.cpp"
    "src/Input/Mouse/Mouse.h"
    "src/Input/Mouse/Mouse.cpp"
    "src/Input/Keys/Keys.h"
    "src/Input/Keys/Keys.cpp"
    "src/Logging/Logging.h"
    "src/Logging/Logging.cpp"
    "src/Memory/VBO.h"
    "src/Memory/VBO.cpp"
    "src/Memory/VAO.h"
    "src/Memory/VAO.cpp"
    "src/Shaders/Shader.h"
    "src/Shaders/Shader.cpp"
    "src/Shaders/Program.h"
    "src/Shaders/Program.cpp"
    "src/Window/Window.h"
    "src/Window/Window.cpp"
)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(Render ${src_files})
link_libraries(Render ${src_files})

target_link_libraries (${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries (${PROJECT_NAME} PRIVATE glfw)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})