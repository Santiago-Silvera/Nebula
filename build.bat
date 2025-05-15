@echo off

:: Create build directory and run cmake to generate the Visual Studio solution
cmake -G "MinGW Makefiles" -S . -B build -DCMAKE_BUILD_TYPE=Debug

:: Change to build directory
cd build

:: Build the project using MSBuild
make

:: Go back to the root directory
cd ..

:: Run the executable (replace "render" with your actual executable name)
.\build\render.exe

pause
