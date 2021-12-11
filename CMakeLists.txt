cmake_minimum_required(VERSION 3.0.0)
project(Render)

set(src_files
    src/main.cpp
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