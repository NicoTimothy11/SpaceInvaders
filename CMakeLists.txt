cmake_minimum_required(VERSION 3.0)  # Specify the minimum CMake version required

project(SpaceInvaders)  # Replace with your project name

# Define the executable and list your source files
add_executable(myApp main.cpp)
target_link_libraries(myApp -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows)


