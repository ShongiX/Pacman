cmake_minimum_required(VERSION 3.25)
project(pacman) # Your Project Name

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add GLAD library
add_library(glad STATIC glad.c)

# Add GLFW library
link_directories(lib-mingw-w64)
add_library(glfw STATIC lib-mingw-w64/libglfw3.a lib-mingw-w64/libglfw3dll.a)
set_target_properties(glfw PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(glfw PRIVATE ${CMAKE_DL_LIBS})

# Add GLM library
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE include/glm)

# Add executable and link libraries
add_executable(pacman src/main.cpp src/View/stb_image.cpp src/System.cpp src/System.hpp src/View/TexturedRectangle.cpp src/View/TexturedRectangle.hpp src/Model/Game.cpp src/Model/Game.hpp src/Model/GameData.hpp src/Enums.hpp src/View/Widget.cpp src/View/Widget.hpp src/View/Menu.cpp src/View/Menu.hpp src/Controller.cpp src/Controller.hpp src/Model/Entity.cpp src/Model/Entity.hpp src/Model/StaticEntity.cpp src/Model/StaticEntity.hpp src/Model/DynamicEntity.cpp src/Model/DynamicEntity.hpp src/Model/Pacman.cpp src/Model/Pacman.hpp src/Model/Map.cpp src/Model/Map.hpp)
target_link_libraries(pacman glad glfw glm ${CMAKE_DL_LIBS} gdi32 user32 kernel32 libglfw3.a)
