//
// Created by laccs on 4/7/2023.
//

#include "Widget.hpp"
#include "Menu.hpp"

Widget::Widget(Menu *m) : m(m) {
    m->addWidget(this);
}