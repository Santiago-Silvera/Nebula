cmake_minimum_required(VERSION 3.3)
project(RenderingEngine C)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable(render
    ${SRC_DIR}/main.c
    ${SRC_DIR}/shader.c
    ${SRC_DIR}/VAO.c
    ${SRC_DIR}/VBO.c
    ${SRC_DIR}/EBO.c
    ${SRC_DIR}/texture.c
    ${SRC_DIR}/stb.c
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
target_link_libraries(render PRIVATE glfw)

add_subdirectory(glad/)
target_link_libraries(render PRIVATE glad)

target_include_directories(render PUBLIC "${PROJECT_SOURCE_DIR}/stb")
target_include_directories(render PUBLIC "${PROJECT_SOURCE_DIR}/include")
