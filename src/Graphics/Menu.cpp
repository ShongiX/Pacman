//
// Created by csong on 4/7/2023.
//

#include "../System.hpp"
#include "Menu.hpp"
#include "../Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Game/GameData.hpp"

void Menu::draw() {
    for (Widget* widget : widgets) widget->draw();
}

void Menu::addWidget(Widget *w) {
    this->widgets.push_back(w);
}

void Menu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {

}




GameMenu::GameMenu() {

}

void GameMenu::setInfo(GameData* _gd) {
    this->gd = _gd;
}

void GameMenu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (Controller::askIfCanTurn(LEFT)) {
            Controller::turn(LEFT);
        }
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (Controller::askIfCanTurn(RIGHT)) {
            Controller::turn(RIGHT);
        }
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (Controller::askIfCanTurn(UP)) {
            Controller::turn(UP);
        }
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (Controller::askIfCanTurn(DOWN)) {
            Controller::turn(DOWN);
        }
    }
}

void GameMenu::update() {
    pacman_trans = glm::mat4(1.0f);
    pacman_trans = glm::translate(pacman_trans, glm::vec3((gd->pacman.getX() - 14.0f) / 14.0f, (18.0f - gd->pacman.getY()) / 18.0f, 0.0f));
    pacman_trans = glm::scale(pacman_trans, glm::vec3(1.0 / 28, 1.0 / 36, 1));
    //pacman_trans = glm::translate(pacman_trans,  glm::vec3(System::getScreenWidth() / 28.0f / (System::getScreenWidth() / 2.0f), 0.0f, 0.0f));
    //pacman_trans = glm::translate(pacman_trans, glm::vec3(gd->pacman.getX() / 14.0f - 1.0f, gd->pacman.getY() / 15.5f - 1.0f, 0.0f));

    //pacman_trans = glm::translate(pacman_trans, glm::vec3(gd->pacman.getX(), gd->pacman.getY()-36, 0));


    //std::cout << gd->pacman.getX() << " " << gd->pacman.getY() << "\n";

    //pacman_trans = glm::translate(pacman_trans, glm::vec3(10, 0, 0));

    pacman->setTrans(pacman_trans);
}


