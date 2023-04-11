//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "GameData.hpp"

class Game {
    GameData* gd;
    bool chase = false;
    const float MOVE_STEP = 0.1;

public:
    Game();
    GameData* getInfo();

    void update();
    void updatePacman();
    void updateGhosts();
    void updateStates();
    void flip();

    bool checkIfCanTurn(Direction direction);
    void turn(Direction direction);
    bool checkIfCanMove(DynamicEntity* entity);
    void move(DynamicEntity* entity);
    void eat();

    void turnGhost(Ghost* ghost);
    bool checkIfCanMoveGhost(Ghost* ghost);
    void moveGhost(Ghost* ghost);
    void setIfOutside(Ghost* ghost);

    bool checkIfWon();
    bool checkIfDead();

    void enableNext();
};


#endif //PACMAN_GAME_HPP
