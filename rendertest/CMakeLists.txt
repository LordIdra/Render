cmake_minimum_required(VERSION 3.0.0)
project(rendertest)

set(src_files
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${src_files})

target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC render)