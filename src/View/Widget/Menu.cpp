//
// Created by csong on 4/7/2023.
//

#include <algorithm>
#include "../../System.hpp"
#include "Menu.hpp"
#include "../../Controller/Controller.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Menu::draw() {
    for (Widget *widget: widgets) widget->draw();
    widgets[widgets.size() - 1]->draw();
}

void Menu::addWidget(Widget *w) {
    this->widgets.push_back(w);
}

void Menu::removeWidget(Widget *w) {
    auto newEnd = std::remove_if(widgets.begin(), widgets.end(), [w](const Widget *widget) {
        return widget == w;
    });
    widgets.erase(newEnd, widgets.end());
}

void Menu::handle(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

GameMenu::GameMenu() {
    lastTime = glfwGetTime();
    nowTime = lastTime;

    //map
    glm::mat4 map_trans = glm::mat4(1.0f);
    map_trans = glm::translate(map_trans, glm::vec3(0, -1 / 36.0, 0));
    map_trans = glm::scale(map_trans, glm::vec3(1, 31.0 / 36.0, 1));

    this->map = new TexturedRectangle(
            this,
            "../assets/map.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            map_trans
    );

    this->pacman_trans = glm::scale(this->pacman_trans, glm::vec3(1.0 / 28.0, 1.0 / 36.0, 1.0));

    /*this->pacman = new TexturedRectangle(
            this,
            "../assets/pacman_right.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            this->pacman_trans
    );*/

    this->pacman_anim[0] = new TexturedRectangle(
            this,
            "../assets/pacman_right_big.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            this->pacman_trans
    );

    this->pacman_anim[1] = new TexturedRectangle(
            this,
            "../assets/pacman_right.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            this->pacman_trans
    );

    this->pacman_anim[2] = new TexturedRectangle(
            this,
            "../assets/pacman_full.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            this->pacman_trans
    );

    for (auto &ghost_tran: this->ghost_trans) {
        ghost_tran = glm::scale(ghost_tran, glm::vec3(1.5 / 28.0, 1.5 / 36.0, 1.0));
    }

    this->ghosts[0] = new TexturedRectangle(
            this,
            "../assets/blinky.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            ghost_trans[0]
    );

    this->ghosts[1] = new TexturedRectangle(
            this,
            "../assets/pinky.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            ghost_trans[1]
    );

    this->ghosts[2] = new TexturedRectangle(
            this,
            "../assets/inky.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            ghost_trans[2]
    );

    this->ghosts[3] = new TexturedRectangle(
            this,
            "../assets/clyde.png",
            TexturedRectangle::defaultVertices,
            TexturedRectangle::defaultIndices,
            ghost_trans[3]
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
    updateTime();
    updateChase();
    updatePacman();
    updateGhosts();
    checkState();
}

void GameMenu::updateTime() {
    nowTime = glfwGetTime();
    deltaTime += (nowTime - lastTime);
    lastTime = nowTime;
}

void GameMenu::updateChase() {
    //Scatter/Chase
    if (deltaTime > 12.0) {
        Controller::flip();
        deltaTime = 0;
    }
}

void GameMenu::updatePacman() {
    pacman_trans = glm::mat4(1.0f);
    pacman_trans = glm::translate(pacman_trans,
                                  glm::vec3((gd->pacman->getX() - 14.0f) / 14.0f, (18.0f - gd->pacman->getY()) / 18.0f,
                                            0.0f));
    pacman_trans = glm::translate(pacman_trans, glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
    pacman_trans = glm::scale(pacman_trans, glm::vec3(1.0 / 28.0, 1.0 / 36.0, 1.0));


    if (gd->pacman->getDirection() == LEFT) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman->getDirection() == UP) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    } else if (gd->pacman->getDirection() == DOWN) {
        pacman_trans = glm::rotate(pacman_trans, glm::radians(270.0f), glm::vec3(0.0, 0.0, 1.0));
    }

    //pacman->setTrans(pacman_trans);
    pacman_anim[0]->setTrans(pacman_trans);
    pacman_anim[1]->setTrans(pacman_trans);
    pacman_anim[2]->setTrans(pacman_trans);

    int t = deltaTime * 10;
    if (t % 4 == 0) {
        removeWidget(pacman_anim[0]);
        addWidget(pacman_anim[1]);
    } else if (t % 4 == 1) {
        removeWidget(pacman_anim[1]);
        addWidget(pacman_anim[2]);
    } else if (t % 4 == 2) {
        removeWidget(pacman_anim[2]);
        addWidget(pacman_anim[1]);
    } else if (t % 4 == 3) {
        removeWidget(pacman_anim[1]);
        addWidget(pacman_anim[0]);
    }
}

void GameMenu::updateGhosts() {

    for (int i = 0; i < GameData::NUMBER_OF_GHOSTS; ++i) {
        ghost_trans[i] = glm::mat4(1.0f);
        ghost_trans[i] = glm::translate(ghost_trans[i], glm::vec3((gd->ghosts[i]->getX() - 14.0f) / 14.0f,
                                                                  (18.0f - gd->ghosts[i]->getY()) / 18.0f, 0.0f));
        ghost_trans[i] = glm::translate(ghost_trans[i], glm::vec3(0.5 / 14.0, -0.5 / 18.0, 0.0));
        ghost_trans[i] = glm::scale(ghost_trans[i], glm::vec3(1.5 / 28.0, 1.5 / 36.0, 1.0));

        ghosts[i]->setTrans(ghost_trans[i]);
    }
}

void GameMenu::checkState() {
    if (gd->gameWon) {
        System::changeState(WIN);
    }
    if (gd->gameOver) {
        System::changeState(DEAD);
    }
}

void GameMenu::build() {
    widgets.clear();
    widgets.push_back(map);

    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (int j = 0; j < GameData::MAP_WIDTH; ++j) {
            //Code for custom maps
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
            } else*/
            if (gd->map[j][i] == DOT) {
                glm::mat4 dot = glm::mat4(1.0f);
                dot = glm::translate(dot, glm::vec3((j - 14.0f) / 14.0f, (18.0f - i) / 18.0f, 0.0f));
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

    widgets.push_back(ghosts[0]);
    widgets.push_back(ghosts[1]);
    widgets.push_back(ghosts[2]);
    widgets.push_back(ghosts[3]);
    //widgets.push_back(pacman);
    widgets.push_back(pacman_anim[0]);
    //widgets.push_back(pacman_anim[1]);
    //widgets.push_back(pacman_anim[2]);
}

void GameMenu::removeDot(int j, int i) {
    removeWidget(dots[j][i]);
}


