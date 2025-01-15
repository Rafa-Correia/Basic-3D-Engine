@echo off
REM A script to automate CMake build process

REM Set the project directory (change as needed)
set BUILD_DIR=build

REM Remove the existing build directory
if exist %BUILD_DIR% (
    echo Removing existing build directory...
    rmdir /s /q %BUILD_DIR%
)

REM Create a new build directory
echo Creating new build directory...
mkdir %BUILD_DIR%

REM Navigate to the build directory
cd %BUILD_DIR%

REM Run CMake to configure the project
echo Running CMake configuration...
cmake .. -G "MinGW Makefiles"

REM Check for configuration errors
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b %errorlevel%
)

REM Build the project
echo Building the project...
cmake --build .

REM Check for build errors
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

REM Return to the parent directory
cd ..

echo Build completed successfully!
pause
