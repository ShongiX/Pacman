//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "GameData.hpp"

class Game {
    GameData* gd;

public:
    Game();
    GameData* getInfo();

    void update();

    bool checkIfCanTurn(Direction direction);
    void turn(Direction direction);

    bool checkIfCanMove();
};


#endif //PACMAN_GAME_HPP
