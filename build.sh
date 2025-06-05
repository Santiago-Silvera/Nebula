#!/usr/bin/env bash

# Crear (o reutilizar) el directorio build/
echo "Preparando directorio build/..."
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi
cd "$BUILD_DIR"


# Configurar y compilar con CMake
echo "Ejecutando CMake (Debug)..."
cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "Compilando en paralelo..."
cmake --build . -- -j"$(nproc)"
