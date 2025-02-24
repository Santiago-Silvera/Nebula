#!/bin/bash

# Create build directory and run cmake
cmake -S . -B build \
    -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
    -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

cd build
make

cp render.exe /mnt/c/Users/santi/Desktop/

echo "Executable copied to Windows Desktop"

cmd.exe /C "C:\Users\santi\Desktop\render.exe"
