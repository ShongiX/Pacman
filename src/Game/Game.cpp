//
// Created by csong on 4/7/2023.
//

#include <fstream>
#include "Game.hpp"

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
    //TODO
}
