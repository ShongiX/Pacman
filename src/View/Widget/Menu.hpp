//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_MENU_HPP
#define PACMAN_MENU_HPP


#include <vector>
#include "Widget.hpp"
#include "glm.hpp"
#include "../../Model/Game/GameData.hpp"

class GameData;

class System;

class TexturedRectangle;

/**
 * This is the View part of the program, which handles most of the rendering and user input.
 * It keeps track of the widgets that are currently being displayed in the widgets vector.
 */
class Menu {
protected:
    std::vector<Widget *> widgets;

public:
    virtual ~Menu();

    virtual void draw();

    virtual void handle(GLFWwindow *window, int key, int scancode, int action, int mods);

    void addWidget(Widget *w);

    void removeWidget(Widget *w);
};


/**
 * This is the menu that is displayed when the game is started.
 */
class GameMenu : public Menu {
    GameData *gd{};
    double lastTime{}, nowTime{}, deltaTime{};

public:
    GameMenu();

    void setInfo(GameData *_gd);

    //The handle function is overridden to handle the user input during the game
    void handle(GLFWwindow *window, int key, int scancode, int action, int mods) override;

    void build();

    //Update functions
    void update();

    void updateTime();

    void updateChase();

    void updatePacman();

    void updateGhosts();

    void checkState();

    //Translation matrices for the pacman and ghosts
    glm::mat4 pacman_trans = glm::mat4(1.0f);
    glm::mat4 ghost_trans[4] = {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)};

    //The widgets with special properties
    TexturedRectangle *map{};
    TexturedRectangle *pacman_anim[3]{};
    TexturedRectangle *ghosts[4][4]{};
    Widget *dots[GameData::MAP_WIDTH][GameData::MAP_HEIGHT]{};

    void removeDot(int j, int i);
};


#endif //PACMAN_MENU_HPP
