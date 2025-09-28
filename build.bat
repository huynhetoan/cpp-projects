@echo off
echo Building 3D Physics Engine...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
cmake .. -G "Visual Studio 16 2019" -A x64

REM Build the project
cmake --build . --config Release

REM Run the executable
echo.
echo Running physics engine demo...
..\bin\PhysicsEngine3D.exe

pause
