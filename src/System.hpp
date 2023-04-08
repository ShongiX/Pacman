//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_SYSTEM_HPP
#define PACMAN_SYSTEM_HPP

#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "Graphics/shader.h"
#include "Graphics/TexturedRectangle.hpp"
#include "Enums.hpp"
#include <map>

class Game;
class Menu;
class GameMenu;
class Controller;

class System {
    Game* game{};

    unsigned int SCREEN_WIDTH;
    unsigned int SCREEN_HEIGHT;
    GLFWwindow *window{};

    static Menu* activeMenu;
    GameMenu* gameMenu{};
    static std::map<State, Menu*> menus;
    static State state;

    static void changeState(State newState);

    void buildMenu();
    Menu* buildMainMenu();
    Menu* buildGameMenu();

public:
    System(unsigned int screenWidth, unsigned int screenHeight);
    ~System();

    void init();
    void run();




    static void clear(float r = 0.0, float g = 0.0, float b = 0.0);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    void initializeGlfw();
};


#endif //PACMAN_SYSTEM_HPP
