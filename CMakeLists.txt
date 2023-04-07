cmake_minimum_required(VERSION 3.25)
project(pacman) # Your Project Name

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add GLAD library
add_library(glad STATIC glad.c)

# Add GLFW library
#add_library(glfw STATIC lib-mingw-w64/libglfw3.a lib-mingw-w64/libglfw3dll.a)
#set_target_properties(glfw PROPERTIES LINKER_LANGUAGE C)
#target_link_libraries(glfw PRIVATE ${CMAKE_DL_LIBS})

link_directories(lib-mingw-w64)
add_library(glfw STATIC lib-mingw-w64/libglfw3.a lib-mingw-w64/libglfw3dll.a)
set_target_properties(glfw PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(glfw PRIVATE ${CMAKE_DL_LIBS})

# Add GLM library
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE include/glm)

# Add executable and link libraries
add_executable(pacman src/main.cpp src/stb_image.cpp src/System.cpp src/System.hpp src/TexturedRectangle.cpp src/TexturedRectangle.hpp)
target_link_libraries(pacman glad glfw glm ${CMAKE_DL_LIBS} gdi32 user32 kernel32 libglfw3.a)
