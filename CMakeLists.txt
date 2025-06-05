cmake_minimum_required(VERSION 3.28)
project(RenderingEngine C)

# -----------------------------
# 1) Opciones generales
# -----------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_definitions(DEBUG)

# Forzar C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# 2) Definir ruta raíz de fuentes
# -----------------------------
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# -----------------------------
# 3) Obtener lista de fuentes
# -----------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    "${SRC_DIR}/*.c"
)

set(SOURCES ${ENGINE_SOURCES})

list(FILTER SOURCES EXCLUDE REGEX ".*/\\.ccls-cache/.*")

message(STATUS "SOURCES: ${SOURCES}")
# -----------------------------
# 4) Crear ejecutable
# -----------------------------
add_executable(render ${SOURCES})



# -----------------------------
# 5) Vulkan
# -----------------------------
find_package(Vulkan REQUIRED)

# -----------------------------
# 6) GLFW 
# -----------------------------
find_package(glfw3 3.3 REQUIRED)

# -----------------------------
# 7) CGLM 
# -----------------------------
add_subdirectory(external/cglm EXCLUDE_FROM_ALL)

# -----------------------------
# 8) GLAD
# -----------------------------
add_subdirectory(external/glad EXCLUDE_FROM_ALL)

# -----------------------------
# 9) STB
# -----------------------------
set(STB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/stb)

# -----------------------------
# 10) Rutas de inclusión del ejecutable
# -----------------------------
target_include_directories(render
    PUBLIC
        # Carpeta STB (stb_image.h, etc.)
        ${STB_INCLUDE_DIR}

        # Carpeta raíz de nuestros headers
        ${SRC_DIR}
        ${SRC_DIR}/core
        ${SRC_DIR}/logger
        ${SRC_DIR}/graphics
        ${SRC_DIR}/window
        ${SRC_DIR}/vk_backend
)

# -----------------------------
# 11) Enlazar librerías
# -----------------------------
target_link_libraries(render
    PRIVATE
        glfw
	m
	glad
        cglm
        Vulkan::Vulkan
)

# -----------------------------
# 12) Opciones adicionales (opcional)
# -----------------------------
# target_compile_options(render PRIVATE -Wall -Wextra -Wpedantic)
