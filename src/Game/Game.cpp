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
    std::ifstream mapFile("../assets/pacman_map.txt");
    //std::ifstream mapFile("C:/Users/csong/CLionProjects/pacman/assets/pacman_map.txt");

    if (!mapFile.is_open()) {
        std::cout << "Failed to read map";
        exit(1);
    }
    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (int j = 0; j < GameData::MAP_WIDTH; ++j) {
            int x;
            mapFile >> x;

            //std::cout << x << " ";

            if (x == PATH) {
                gd->map[j][i] = PATH;
            } else if (x == WALL) {
                gd->map[j][i] = WALL;
            }
        }
        //std::cout << "\n";
    }

//    for (int i = 0; i < GameData::MAP_WIDTH; ++i) {
//        for (int j = 0; j < GameData::MAP_HEIGHT; ++j) {
//            std::cout << gd->map[i][j] << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";
}

GameData *Game::getInfo() {
    return gd;
}

void Game::update() {
    //std::cout << "game updated\n";
    if (!checkIfCanMove()) return;

    if (gd->pacman.getDirection() == LEFT) {
        gd->pacman.move(-0.1,0);
        //std::cout << "moving left\n";
        //std::cout << gd->pacman_trans.getX() << std::endl;

    } else if (gd->pacman.getDirection() == RIGHT) {
        gd->pacman.move(0.1,0);
    } else if (gd->pacman.getDirection() == UP) {
        gd->pacman.move(0,-0.1);
    } else if (gd->pacman.getDirection() == DOWN) {
        gd->pacman.move(0,0.1);
    }
}

bool Game::checkIfCanTurn(Direction direction) {
    if (direction == gd->pacman.getDirection()) return false;

    std::cout << "checking if can turn\n";

    if (direction == LEFT && gd->map[(int)std::round(gd->pacman.getX())-1][(int)std::round(gd->pacman.getY())] == PATH) {
        return true;
    } else if (direction == RIGHT && gd->map[(int)std::round(gd->pacman.getX())+1][(int)std::round(gd->pacman.getY())] == PATH) {
        return true;
    } else if (direction == UP && gd->map[(int)std::round(gd->pacman.getX())][(int)std::round(gd->pacman.getY())-1] == PATH) {
        return true;
    } else if (direction == DOWN && gd->map[(int)std::round(gd->pacman.getX())][(int)std::round(gd->pacman.getY())+1] == PATH) {
        return true;
    }

    return false;
}

bool Game::checkIfCanMove() {
    //std::cout << (int)std::round(gd->pacman.getX()) << " " << (int)std::round(gd->pacman.getY()) << " " << gd->map[(int)std::round(gd->pacman.getX())][(int)std::round(gd->pacman.getY())] << "\n";
    if (gd->pacman.getDirection() == LEFT && gd->map[(int)std::round(gd->pacman.getX())-1][(int)std::round(gd->pacman.getY())] == PATH) {
        return true;
    } else if (gd->pacman.getDirection() == RIGHT && gd->map[(int)std::round(gd->pacman.getX())+1][(int)std::round(gd->pacman.getY())] == PATH) {
        return true;
    } else if (gd->pacman.getDirection() == UP && gd->map[(int)std::round(gd->pacman.getX())][(int)std::round(gd->pacman.getY())-1] == PATH) {
        return true;
    } else if (gd->pacman.getDirection() == DOWN && gd->map[(int)std::round(gd->pacman.getX())][(int)std::round(gd->pacman.getY())+1] == PATH) {
        return true;
    }

    return false;
}

void Game::turn(Direction direction) {
    std::cout << "turned\n";
    gd->pacman.setDirection(direction);
}

