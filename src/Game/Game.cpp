//
// Created by csong on 4/7/2023.
//

#include "../System.hpp"
#include <fstream>
#include <cmath>
#include "Game.hpp"
#include "../Controller.hpp"
#include "../Graphics/Menu.hpp"
#include "glm/gtc/matrix_transform.hpp"


Game::Game() {
    gd = new GameData();

    //Read and load map info
    std::ifstream mapFile("../../assets/pacman_map.txt");
    for (int i = 0; i < GameData::MAP_WIDTH; ++i) {
        for (int j = 0; j < GameData::MAP_HEIGHT; ++j) {
            int x;
            mapFile >> x;

            if (x == PATH) {
                gd->map[i][j] = PATH;
            } else if (x == WALL) {
                gd->map[i][j] = WALL;
            }
        }
    }
}

GameData *Game::getInfo() {
    return gd;
}

void Game::update() {
    if (pacman.getDirection() == LEFT) {
        pacman.move(-0.1,0);
        Controller::gameMenu->pacman = glm::translate(Controller::gameMenu->pacman, glm::vec3(System::getScreenWidth() / 28.0f / (System::getScreenWidth() / 2.0f), 0.0f, 0.0f));
    } else if (pacman.getDirection() == RIGHT) {
        pacman.move(0.1,0);
    } else if (pacman.getDirection() == UP) {
        pacman.move(0,0.1);
    } else if (pacman.getDirection() == DOWN) {
        pacman.move(0,-0.1);
    }
}

bool Game::checkIfCanTurn(Direction direction) {
    if (direction == pacman.getDirection()) return false;

    if (direction == LEFT && gd->map[(int)std::round(pacman.getX())-1][(int)std::round(pacman.getY())] == PATH) {
        return true;
    }

    return false;
}

void Game::turn(Direction direction) {
    pacman.setDirection(direction);
}

