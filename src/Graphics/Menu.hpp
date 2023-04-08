//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_MENU_HPP
#define PACMAN_MENU_HPP


#include <vector>
#include "Widget.hpp"

class GameData;

class Menu {
protected:
    std::vector<Widget*> widgets;

public:
    virtual void draw();

    void addWidget(Widget *w);
};

class GameMenu : public Menu {
    GameData* gd{};

public:
    void update();
    void build();
    void setInfo(GameData* _gd);
};


#endif //PACMAN_MENU_HPP
