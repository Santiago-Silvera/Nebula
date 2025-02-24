@echo off

:: Create build directory and run cmake
cmake -G "MinGW MakeFiles" -S . -B build

:: Change to build directory
cd build

:: Build the project using MSBuild (if using Visual Studio) or MinGW (if using GCC)
:: For MinGW-w64 (GCC):
 make
:: For MSVC (Visual Studio), uncomment the next line:
:: msbuild your_project.sln /p:Configuration=Release

:: Go back to the root directory
cd ..

:: Run the executable (replace "render" with your actual executable name)
.\build\render.exe

pause

