cmake_minimum_required(VERSION 3.0.0)
project(render)

set(include_files
    
)

set(src_files
    "include/Camera/Camera.h"
    "src/Camera/Camera.cpp"
    "include/Core/Core.h"
    "src/Core/Core.cpp"
    "include/Geometry/Geometry.h"
    "src/Geometry/Geometry.cpp"
    "include/Input/Mouse.h"
    "src/Input/Mouse.cpp"
    "include/Input/Keys.h"
    "src/Input/Keys.cpp"
    "include/Logging/Logging.h"
    "src/Logging/Logging.cpp"
    "include/Memory/EBO.h"
    "src/Memory/EBO.cpp"
    "include/Memory/VBO.h"
    "src/Memory/VBO.cpp"
    "include/Memory/VAO.h"
    "src/Memory/VAO.cpp"
    "include/Shaders/Shader.h"
    "src/Shaders/Shader.cpp"
    "include/Shaders/Program.h"
    "src/Shaders/Program.cpp"
    "include/Window/Window.h"
    "src/Window/Window.cpp"
)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(${PROJECT_NAME} ${src_files} ${include_files})
link_libraries(${PROJECT_NAME} ${src_files} ${include_files})

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/depend)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries (${PROJECT_NAME} PRIVATE glfw)