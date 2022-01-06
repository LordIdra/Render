cmake_minimum_required(VERSION 3.10.0)
project(render)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(src_files
    "src/Camera/Camera.cpp"
    "src/Init/init.cpp"
    "src/Geometry/Geometry.cpp"
    "src/Input/mouse.cpp"
    "src/Input/keys.cpp"
    "src/Logging/logging.cpp"
    "src/Memory/EBO.cpp"
    "src/Memory/VBO.cpp"
    "src/Memory/VAO.cpp"
    "src/Shaders/Shader.cpp"
    "src/Shaders/Program.cpp"
    "src/Window/window.cpp"
)

set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(${PROJECT_NAME} ${src_files} ${include_files})
link_libraries(${PROJECT_NAME} ${src_files} ${include_files})

target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries (${PROJECT_NAME} PRIVATE glfw)