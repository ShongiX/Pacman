//
// Created by csong on 4/7/2023.
//

#include "../System.hpp"
#include <fstream>
#include <cmath>
#include "Game.hpp"
#include "../View/Menu.hpp"
#include "../Controller.hpp"


Game::Game() {
    gd = new GameData();

    //Read and load map info
    std::ifstream mapFile("../assets/pacman_map.txt");
    if (!mapFile.is_open()) {
        std::cout << "Failed to read map";
        exit(1);
    }
    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (int j = 0; j < GameData::MAP_WIDTH; ++j) {
            int x;
            mapFile >> x;

            if (x == PATH) {
                gd->map[j][i] = PATH;
            } else if (x == WALL) {
                gd->map[j][i] = WALL;
            } else if (x == DOT) {
                gd->map[j][i] = DOT;
            } else if (x == GHOST_ONLY) {
                gd->map[j][i] = GHOST_ONLY;
            }
        }
    }
}

GameData *Game::getInfo() {
    return gd;
}

void Game::update() {
    //std::cout << gd->pacman.getX() << " " << gd->pacman.getY() << "\n";

    move();
    eat();

    if (checkIfWon()) gd->gameWon = true;
}

bool Game::checkIfCanTurn(Direction direction) {
    if (direction == gd->pacman.getDirection()) return false;
    if ((direction == LEFT && gd->pacman.getDirection() == RIGHT) ||
        (direction == RIGHT && gd->pacman.getDirection() == LEFT) ||
        (direction == UP && gd->pacman.getDirection() == DOWN) ||
        (direction == DOWN && gd->pacman.getDirection() == UP)) {
        return false;
    }

    float x = gd->pacman.getX();
    float y = gd->pacman.getY();
    int r = std::round(x);
    int c = std::round(y);
    if (direction == LEFT) {
        if (gd->map[r][c] != WALL && gd->map[r - 1][c] != WALL) {
            return true;
        }
    } else if (direction == RIGHT) {
        if (gd->map[r][c] != WALL && gd->map[r + 1][c] != WALL) {
            return true;
        }
    } else if (direction == UP) {
        if (gd->map[r][c] != WALL && gd->map[r][c - 1] != WALL) {
            return true;
        }
    } else if (direction == DOWN) {
        if (gd->map[r][c] != WALL && gd->map[r][c + 1] != WALL) {
            return true;
        }
    }

    return false;
}

void Game::turn(Direction direction) {
    gd->pacman.setDirection(direction);
    gd->pacman.norm();
}

bool Game::checkIfCanMove() {
    if (gd->pacman.getDirection() == LEFT &&
        gd->map[(int) std::round(gd->pacman.getX() - 0.5)][(int) std::round(gd->pacman.getY())] != WALL) {
        return true;
    } else if (gd->pacman.getDirection() == RIGHT &&
               gd->map[(int) std::round(gd->pacman.getX() + 0.5)][(int) std::round(gd->pacman.getY())] != WALL) {
        return true;
    } else if (gd->pacman.getDirection() == UP &&
               gd->map[(int) std::round(gd->pacman.getX())][(int) std::round(gd->pacman.getY() - 0.5)] != WALL) {
        return true;
    } else if (gd->pacman.getDirection() == DOWN &&
               gd->map[(int) std::round(gd->pacman.getX())][(int) std::round(gd->pacman.getY() + 0.5)] != WALL) {
        return true;
    }

    return false;
}

void Game::move() {
    if (!checkIfCanMove()) return;

    if (gd->pacman.getDirection() == LEFT) {
        gd->pacman.move(-0.1, 0);
        if (gd->pacman.getX() < -0.5) gd->pacman.setX(28);
    } else if (gd->pacman.getDirection() == RIGHT) {
        gd->pacman.move(0.1, 0);
        if (gd->pacman.getX() > 28.5) gd->pacman.setX(0);
    } else if (gd->pacman.getDirection() == UP) {
        gd->pacman.move(0, -0.1);
    } else if (gd->pacman.getDirection() == DOWN) {
        gd->pacman.move(0, 0.1);
    }
}

void Game::eat() {
    if (gd->map[(int) std::round(gd->pacman.getX())][(int) std::round(gd->pacman.getY())] == DOT) {
        gd->map[(int) std::round(gd->pacman.getX())][(int) std::round(gd->pacman.getY())] = PATH;
        Controller::deleteDot((int) std::round(gd->pacman.getX()), (int) std::round(gd->pacman.getY()));
        --gd->numberOfDots;
    }
}

bool Game::checkIfWon() {
    return gd->numberOfDots == 0;
}



