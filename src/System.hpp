//
// Created by laccs on 4/7/2023.
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

/**
 * A wrapper class for the main, so everything can be initialized and run from here.
 * It also handles the state of the game, the menus and the window.
 * It also handles the callbacks for the window.
 */
class System {
    GLFWwindow *window{};

    static unsigned int SCREEN_WIDTH;
    static unsigned int SCREEN_HEIGHT;

    //The different menus
    static Game *game;
    static Menu *activeMenu;
    static GameMenu *gameMenu;
    static std::map<State, Menu *> menus;
    static State state;

    // Setting up the different menus
    static void buildMenu();

    static Menu *buildMainMenu();

    static Menu *buildGameMenu();

    static Menu *buildWinMenu();

    static Menu *buildDeadMenu();

public:
    System(unsigned int screenWidth, unsigned int screenHeight);

    ~System();

    // Clear the screen
    static void clear(float r = 0.0, float g = 0.0, float b = 0.0);

    // Initialize the game, used for restarting the game
    static void init();

    // Main loop
    void run();

    static void handle(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void setScreenWidth(unsigned int screenWidth);

    static void setScreenHeight(unsigned int screenHeight);

    static State getState();

    static void changeState(State newState);

    void initializeGlfw();
};


#endif //PACMAN_SYSTEM_HPP
