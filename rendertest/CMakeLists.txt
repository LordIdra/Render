cmake_minimum_required(VERSION 3.10.0)
project(rendertest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(src_files
    "main.cpp"
    "src/Chunk.cpp"
    "src/debug.cpp"
    "src/indices.cpp"
    "src/move.cpp"
    "src/Visualiser.cpp"
    "src/TerrainStorage.cpp"
    "src/zoom.cpp"
)

add_executable(${PROJECT_NAME} ${src_files})

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC render)