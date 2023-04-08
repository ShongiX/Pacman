//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_WIDGET_HPP
#define PACMAN_WIDGET_HPP


#include "GLFW/glfw3.h"

class Menu;

class Widget {
protected:
    Menu *m{};
public:
    virtual void draw() = 0;

    explicit Widget(Menu *m);
    Widget() = default;;
};


#endif //PACMAN_WIDGET_HPP
