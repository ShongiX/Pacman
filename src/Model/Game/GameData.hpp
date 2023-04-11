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

/**
 * GameData contains all the data needed for the game to run, and is shared between Game and GameMenu.
 * It is a friend of Game and GameMenu, so they can access its private members.
 */
class GameData {
public:
    static const int MAP_WIDTH = 28;
    static const int MAP_HEIGHT = 36;

    static const int NUMBER_OF_GHOSTS = 4;

private:
    //Logical map
    Tile map[MAP_WIDTH][MAP_HEIGHT]{};

    //Game state
    bool gameOver = false;
    bool gameWon = false;

    //Counted when loading the map
    int numberOfDots = 0;

    //Number of enabled ghosts
    int enabled = 1;

    Pacman* pacman{};
    Ghost* ghosts[4]{};

    friend Game;
    friend GameMenu;
};

#endif //PACMAN_GAMEDATA_HPP
