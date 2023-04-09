//
// Created by csong on 4/7/2023.
//

#include <algorithm>
#include "../System.hpp"
#include "Menu.hpp"
#include "../Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Model/GameData.hpp"

void Menu::draw() {
    for (Widget *widget: widgets) widget->draw();
    widgets[widgets.size()-1]->draw();
}

void Menu::addWidget(Widget *w) {
    this->widgets.push_back(w);
}

void Menu::removeWidget(Widget *w) {
    auto newEnd = std::remove_if(widgets.begin(), widgets.end(), [w](const Widget* widget) {
        return widget == w;
    });
    widgets.erase(newEnd, widgets.end());
}

void Menu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

GameMenu::GameMenu() {

}

void GameMenu::setInfo(GameData *_gd) {
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
    //pacman_trans = glm::translate(pacman_trans, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
    pacman_trans = glm::translate(pacman_trans,glm::vec3((gd->pacman.getX() - 14.0f) / 14.0f, (18.0f - gd->pacman.getY()) / 18.0f,0.0f));
    pacman_trans = glm::translate(pacman_trans, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
    pacman_trans = glm::scale(pacman_trans, glm::vec3(1.0 / 28.0, 1.0 / 36.0, 1.0));


    if (gd->pacman.getDirection() == LEFT) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman.getDirection() == UP) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman.getDirection() == DOWN) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(270.0f), glm::vec3(0.0, 0.0, 1.0));
    }

    //std::cout << gd->pacman.getX() << " " << gd->pacman.getY() << "\n";
    pacman->setTrans(pacman_trans);
}

void GameMenu::build() {
    Widget* tmp_board = widgets.at(0);
    Widget* tmp_pacman = widgets.at(1);
    //Widget *tmp_pacman = widgets.at(0);
    widgets.clear();
    widgets.push_back(tmp_board);

    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (int j = 0; j < GameData::MAP_WIDTH; ++j) {
            /*if (gd->map[j][i] == WALL) {
                glm::mat4 tile = glm::mat4(1.0f);
                tile = glm::translate(tile,glm::vec3((j - 14.0f) / 14.0f, (18.0f - i) / 18.0f,0.0f));
                tile = glm::translate(tile, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
                tile = glm::scale(tile, glm::vec3(1.0 / 28.0, 1.0 / 36.0, 1.0));

                new TexturedRectangle(this,
                                      "../assets/wall.png",
                                      TexturedRectangle::defaultVertices,
                                      TexturedRectangle::defaultIndices,
                                      tile
                );
            } else*/ if (gd->map[j][i] == DOT) {
                glm::mat4 dot = glm::mat4(1.0f);
                dot = glm::translate(dot,glm::vec3((j - 14.0f) / 14.0f, (18.0f - i) / 18.0f,0.0f));
                dot = glm::translate(dot, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
                dot = glm::scale(dot, glm::vec3(0.5 / 28.0, 0.5 / 36.0, 1.0));

                dots[j][i] = new TexturedRectangle(this,
                                      "../assets/dot.png",
                                      TexturedRectangle::defaultVertices,
                                      TexturedRectangle::defaultIndices,
                                      dot
                );
            }
        }
    }

    widgets.push_back(tmp_pacman);
}

void GameMenu::removeDot(int j, int i) {
    removeWidget(dots[j][i]);
}


