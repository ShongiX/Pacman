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
    //map
    glm::mat4 map = glm::mat4(1.0f);
    map = glm::translate(map, glm::vec3(0, -1 / 36.0, 0));
    map = glm::scale(map, glm::vec3(1, 31.0 / 36.0, 1));

    new TexturedRectangle(
            this,
            "../assets/map.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            map
    );

    pacman = new TexturedRectangle(
            this,
            "../assets/pacman_right.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            pacman_trans
    );

    blinky = new TexturedRectangle(
            this,
            "../assets/blinky.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            blinky_trans
    );
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
    updatePacman();
    updateBlinky();
    checkState();
}

void GameMenu::updatePacman() {
    pacman_trans = glm::mat4(1.0f);
    pacman_trans = glm::translate(pacman_trans,glm::vec3((gd->pacman->getX() - 14.0f) / 14.0f, (18.0f - gd->pacman->getY()) / 18.0f,0.0f));
    pacman_trans = glm::translate(pacman_trans, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
    pacman_trans = glm::scale(pacman_trans, glm::vec3(1.0 / 28.0, 1.0 / 36.0, 1.0));


    if (gd->pacman->getDirection() == LEFT) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman->getDirection() == UP) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman->getDirection() == DOWN) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(270.0f), glm::vec3(0.0, 0.0, 1.0));
    }

    pacman->setTrans(pacman_trans);
}

void GameMenu::updateBlinky() {
    blinky_trans = glm::mat4(1.0f);
    blinky_trans = glm::translate(blinky_trans,glm::vec3((gd->blinky->getX() - 14.0f) / 14.0f, (18.0f - gd->blinky->getY()) / 18.0f,0.0f));
    blinky_trans = glm::translate(blinky_trans, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
    blinky_trans = glm::scale(blinky_trans, glm::vec3(1.5 / 28.0, 1.5 / 36.0, 1.0));

    blinky->setTrans(blinky_trans);
}

void GameMenu::checkState() {
    if (gd->gameWon) {
        System::changeState(WIN);

        //Win text
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.8, 0.3, 1));

        new TexturedRectangle(
                this,
                "../assets/win_text.png",
                TexturedRectangle::defaultVertices,
                TexturedRectangle::defaultIndices,
                trans
        );
    }
    if (gd->gameOver) {
        System::changeState(DEAD);

        //Dead text
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.8, 0.3, 1));

        new TexturedRectangle(
                this,
                "../assets/dead_text.png",
                TexturedRectangle::defaultVertices,
                TexturedRectangle::defaultIndices,
                trans
        );
    }
}

void GameMenu::build() {
    Widget* tmp_board = widgets.at(0);
    Widget* tmp_pacman = widgets.at(1);
    Widget* tmp_blinky = widgets.at(2);
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
    widgets.push_back(tmp_blinky);
}

void GameMenu::removeDot(int j, int i) {
    removeWidget(dots[j][i]);
}


