//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "GameData.hpp"
#include "Pacman.hpp"

class Game {
    GameData* gd;

    Pacman pacman;

public:
    Game();
    GameData* getInfo();

    void update();

    bool checkIfCanTurn(Direction direction);
    void turn(Direction direction);
};


#endif //PACMAN_GAME_HPP
