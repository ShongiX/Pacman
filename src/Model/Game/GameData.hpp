//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_GAMEDATA_HPP
#define PACMAN_GAMEDATA_HPP

#include "../../Enums.hpp"
#include "../Entity/Pacman/Pacman.hpp"
#include "../Entity/Ghost/Blinky.hpp"

class Game;
class GameMenu;

class GameData {
public:
    static const int MAP_WIDTH = 28;
    static const int MAP_HEIGHT = 36;

    static const int NUMBER_OF_GHOSTS = 4;

private:
    Tile map[MAP_WIDTH][MAP_HEIGHT];

    bool gameOver = false;
    bool gameWon = false;
    int numberOfDots = 246;
    int enabled = 1; //number of enabled ghosts

    Pacman* pacman;
    Ghost* ghosts[4];
    //Blinky* blinky;

    friend Game;
    friend GameMenu;
};

#endif //PACMAN_GAMEDATA_HPP
