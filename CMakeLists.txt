# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(3DGameEngine VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable (source files will go here)
add_executable(GameEngine 
    src/main.cpp
    src/graphics/basic_graphics.cpp    
    
    src/utils/glad.c
)

# Include Folder
include_directories(include)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(GameEngine OpenGL::GL glfw)
