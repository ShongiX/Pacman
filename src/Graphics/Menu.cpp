//
// Created by csong on 4/7/2023.
//

#include "../System.hpp"
#include "Menu.hpp"
#include "../Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Menu::draw() {
    for (Widget* widget : widgets) widget->draw();
}

void Menu::addWidget(Widget *w) {
    this->widgets.push_back(w);
}

void Menu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

void GameMenu::setInfo(GameData* _gd) {
    this->gd = _gd;
}

void GameMenu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (Controller::askIfCanTurn(LEFT)) {
            Controller::turn(LEFT);
            pacman = glm::translate(pacman, glm::vec3(System::getScreenWidth() / 28.0f / (System::getScreenWidth() / 2.0f), 0.0f, 0.0f));
        }
    }
}
