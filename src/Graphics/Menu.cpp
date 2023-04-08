//
// Created by csong on 4/7/2023.
//

#include <string>
#include "Menu.hpp"
#include "../Game/GameData.hpp"

void Menu::draw() {
    for (Widget* widget : widgets) widget->draw();
}

void Menu::addWidget(Widget *w) {
    this->widgets.push_back(w);
}

void GameMenu::update() {
    //TODO
}

void GameMenu::build() {
    //TODO
}

void GameMenu::setInfo(GameData* _gd) {
    this->gd = _gd;
}