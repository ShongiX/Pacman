//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_MENU_HPP
#define PACMAN_MENU_HPP


#include <vector>
#include "Widget.hpp"
#include "glm.hpp"
#include "../../Model/GameData.hpp"

class GameData;

class System;

class TexturedRectangle;

class Menu {
protected:
    std::vector<Widget *> widgets;

public:
    virtual void draw();

    virtual void handle(GLFWwindow *window, int key, int scancode, int action, int mods);

    void addWidget(Widget *w);

    void removeWidget(Widget *w);
};


class GameMenu : public Menu {
    GameData *gd{};
    double lastTime{}, nowTime{}, deltaTime{};

public:
    GameMenu();

    void setInfo(GameData *_gd);

    void handle(GLFWwindow *window, int key, int scancode, int action, int mods) override;

    void build();

    void update();

    void updateTime();

    void updateChase();

    void updatePacman();

    void updateGhosts();

    void checkState();

    //Translation matrices
    glm::mat4 pacman_trans = glm::mat4(1.0f);
    glm::mat4 ghost_trans[4] = {glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f)};

    TexturedRectangle *map{};
    TexturedRectangle *pacman_anim[3]{};
    TexturedRectangle *ghosts[4][4]{};

    Widget *dots[GameData::MAP_WIDTH][GameData::MAP_HEIGHT]{};

    void removeDot(int j, int i);
};


#endif //PACMAN_MENU_HPP
