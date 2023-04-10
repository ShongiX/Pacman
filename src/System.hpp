//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_SYSTEM_HPP
#define PACMAN_SYSTEM_HPP

#include "glad/glad.h"
#include "View/Widget/TexturedRectangle.hpp"
#include "Enums.hpp"
#include <map>

class Game;
class Menu;
class GameMenu;
class Controller;

class System {
    static Game* game;

    static unsigned int SCREEN_WIDTH;
    static unsigned int SCREEN_HEIGHT;
    static unsigned int REFRESH;

    GLFWwindow *window{};

    static Menu* activeMenu;
    static GameMenu* gameMenu;
    static std::map<State, Menu*> menus;
    static State state;

    void buildMenu();
    static Menu* buildMainMenu();
    static Menu* buildGameMenu();
    static Menu* buildWinMenu();
    static Menu* buildDeadMenu();

public:
    System(unsigned int screenWidth, unsigned int screenHeight, unsigned int refresh);
    ~System();

    static void init();
    void run();

    static unsigned int getScreenWidth();
    static unsigned int getScreenHeight();

    static void setScreenWidth(unsigned int screenWidth);
    static void setScreenHeight(unsigned int screenHeight);

    static State getState();
    static void changeState(State newState);

    static void clear(float r = 0.0, float g = 0.0, float b = 0.0);

    static void handle(GLFWwindow *window, int key, int scancode, int action, int mods);

    void initializeGlfw();
};


#endif //PACMAN_SYSTEM_HPP
