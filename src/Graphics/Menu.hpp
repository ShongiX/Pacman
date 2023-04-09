//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_MENU_HPP
#define PACMAN_MENU_HPP


#include <vector>
#include "Widget.hpp"
#include "glm.hpp"

class GameData;
class System;
class TexturedRectangle;

class Menu {
protected:
    std::vector<Widget*> widgets;

public:
    virtual void draw();
    virtual void handle(GLFWwindow *window, int key, int scancode, int action, int mods);

    void addWidget(Widget *w);
};


class GameMenu : public Menu {
    GameData* gd{};

public:
    GameMenu();

    void setInfo(GameData* _gd);
    void handle(GLFWwindow *window, int key, int scancode, int action, int mods) override;
    void update();

    //Translation matrices
    glm::mat4 map = glm::mat4(1.0f);
    glm::mat4 pacman_trans = glm::mat4(1.0f);

    TexturedRectangle* pacman;
};


#endif //PACMAN_MENU_HPP
