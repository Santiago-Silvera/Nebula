#!/usr/bin/env bash

# TODO: I still need to manage how to download glad. For now, just install glad
# manually. Sorry.

set -e

#
# 0) Función auxiliar para imprimir pasos
#
function echo_step() {
    echo -e "\n→ $1"
}

#
# 1) Detectar compilador (preferir gcc sobre clang)
#
if command -v gcc >/dev/null 2>&1; then
    CC=gcc
    CXX=g++
    echo_step "Usando GCC: $CC / $CXX"
elif command -v clang >/dev/null 2>&1; then
    CC=clang
    CXX=clang++
    echo_step "GCC no encontrado; usando Clang: $CC / $CXX"
else
    echo "Error: No se encontró ni gcc ni clang." >&2
    exit 1
fi

export CC CXX

#
# 2) Instalar paquetes del sistema necesarios
#
echo_step "Instalando paquetes de Arch Linux requeridos..."
sudo pacman -Sy --needed \
    vulkan-headers \
    vulkan-validation-layers \
    vulkan-icd-loader \
    vulkan-tools \
    xorgproto \
    libx11 \
    libxrandr \
    libxinerama \
    libxcursor \
    libxfixes \
    mesa \
    cmake \
    base-devel \
    git \
    glfw-wayland

#
# 3) Verificar cabeceras Vulkan
#
echo_step "Comprobando cabeceras Vulkan..."
if [[ -f "/usr/include/vulkan/vulkan.h" ]]; then
    echo "→ Vulkan-headers ya presentes."
else
    echo "Error: /usr/include/vulkan/vulkan.h no se encontró." >&2
    exit 1
fi

#
# 4) Verificar runtime Vulkan (pkg-config o vulkaninfo)
#
function has_vulkan_pkgconfig() {
    if command -v pkg-config >/dev/null 2>&1; then
        pkg-config --exists vulkan && return 0
    fi
    return 1
}

function has_vulkaninfo() {
    command -v vulkaninfo >/dev/null 2>&1
}

echo_step "Comprobando runtime Vulkan (ICD loader + herramientas)..."
if has_vulkan_pkgconfig || has_vulkaninfo; then
    echo "→ Runtime Vulkan ya presente."
else
    echo "Error: No se detecta runtime Vulkan luego de instalar paquetes." >&2
    exit 1
fi

#
# 5) Clonar o actualizar dependencias en external/
#
echo_step "Preparando dependencias en carpeta external/..."

if [ ! -d "external" ]; then
    mkdir external
fi

# 5.1) GLFW (subproyecto)
if [ ! -d "external/glfw" ]; then
    echo "  • Clonando GLFW..."
    git clone https://github.com/glfw/glfw.git external/glfw
else
    echo "  • Actualizando GLFW existente..."
    (cd external/glfw && git pull origin master || true)
fi

# 5.3) CGLM (subproyecto)
if [ ! -d "external/cglm" ]; then
    echo "  • Clonando CGLM..."
    git clone https://github.com/recp/cglm.git external/cglm
else
    echo "  • Actualizando CGLM existente..."
    (cd external/cglm && git pull origin master || true)
fi

# 5.4) STB (subproyecto)
if [ ! -d "external/stb" ]; then
    echo "  • Clonando STB..."
    git clone https://github.com/nothings/stb.git external/stb
else
    echo "  • Actualizando STB existente..."
    (cd external/stb && git pull origin master || true)
fi

