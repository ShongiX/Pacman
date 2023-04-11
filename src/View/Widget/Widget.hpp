//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_WIDGET_HPP
#define PACMAN_WIDGET_HPP


#include "GLFW/glfw3.h"

class Menu;

/**
 *  Widget is a base class for all the objects that can be drawn on the screen.
 *  It has a pointer to the Menu object that it belongs to.
 *  It's a pure virtual class, so it can't be instantiated.
 *  It has a virtual destructor, so it can be safely deleted.
 */
class Widget {
protected:
    Menu *m{};
public:
    virtual void draw() = 0;

    explicit Widget(Menu *m);
    Widget() = default;;
    virtual ~Widget() = default;
};


#endif //PACMAN_WIDGET_HPP
