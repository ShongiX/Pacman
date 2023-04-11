//
// Created by laccs on 4/7/2023.
//

#include "Widget.hpp"
#include "Menu.hpp"

// Constructor
Widget::Widget(Menu *m) : m(m) {
    // Add the widget to the menu, so it can be drawn
    m->addWidget(this);
}