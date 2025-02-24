cmake_minimum_required(VERSION 3.28)
project(RenderingEngine C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable(render
    ${SRC_DIR}/main.c
    ${SRC_DIR}/shader.c
    ${SRC_DIR}/VAO.c
    ${SRC_DIR}/VBO.c
    ${SRC_DIR}/EBO.c
    ${SRC_DIR}/texture.c
    ${SRC_DIR}/stb.c
    ${SRC_DIR}/camera.c
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw EXCLUDE_FROM_ALL)

add_subdirectory(external/glad EXCLUDE_FROM_ALL)

add_subdirectory(external/cglm EXCLUDE_FROM_ALL)

target_link_libraries(render PRIVATE glfw glad cglm_headers)

target_include_directories(render PUBLIC "${PROJECT_SOURCE_DIR}/external/stb")
target_include_directories(render PUBLIC "${PROJECT_SOURCE_DIR}/include")

