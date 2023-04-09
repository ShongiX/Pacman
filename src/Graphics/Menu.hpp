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

    //Translation matrices
    glm::mat4 map = glm::mat4(1.0f);



public:
    void setInfo(GameData* _gd);
    void handle(GLFWwindow *window, int key, int scancode, int action, int mods) override;

    glm::mat4 pacman = glm::mat4(1.0f);;
};


#endif //PACMAN_MENU_HPP
