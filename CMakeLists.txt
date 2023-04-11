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
add_executable(pacman src/main.cpp src/View/stb_image.cpp src/System.cpp src/System.hpp src/View/Widget/TexturedRectangle.cpp src/View/Widget/TexturedRectangle.hpp src/Model/Game/Game.cpp src/Model/Game/Game.hpp src/Model/Game/GameData.hpp src/Enums.hpp src/View/Widget/Widget.cpp src/View/Widget/Widget.hpp src/View/Widget/Menu.cpp src/View/Widget/Menu.hpp src/Controller/Controller.cpp src/Controller/Controller.hpp src/Model/Entity/Core/Entity.cpp src/Model/Entity/Core/Entity.hpp src/Model/Entity/Core/DynamicEntity.cpp src/Model/Entity/Core/DynamicEntity.hpp src/Model/Entity/Pacman/Pacman.cpp src/Model/Entity/Pacman/Pacman.hpp src/Model/Entity/Ghost/Ghost.cpp src/Model/Entity/Ghost/Ghost.hpp src/Model/Entity/Ghost/Blinky.cpp src/Model/Entity/Ghost/Blinky.hpp src/Model/Entity/Ghost/Pinky.cpp src/Model/Entity/Ghost/Pinky.hpp src/Model/Entity/Ghost/Inky.cpp src/Model/Entity/Ghost/Inky.hpp src/Model/Entity/Ghost/Clyde.cpp src/Model/Entity/Ghost/Clyde.hpp)
target_link_libraries(pacman glad glfw glm ${CMAKE_DL_LIBS} gdi32 user32 kernel32 libglfw3.a)
