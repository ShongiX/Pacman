//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_GAMEDATA_HPP
#define PACMAN_GAMEDATA_HPP

#include "../Enums.hpp"

class Game;
class GameMenu;

class GameData {
public:
    static const int MAP_WIDTH = 28;
    static const int MAP_HEIGHT = 31;

private:
    Tile map[MAP_WIDTH][MAP_HEIGHT]{};

    bool gameOver = false;
    int score = 0;

    friend Game;
    friend GameMenu;
};

#endif //PACMAN_GAMEDATA_HPP
