//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "GameData.hpp"

/**
 * The model of the game is managed by this class.
 *
 * The game is switching between two modes: scatter mode and chase mode.
 * In scatter mode the ghosts have a designated target tile outside of the actual map and they move towards it.
 * In chase mode the ghosts have a designated target tile inside the map linked to the position of the Pacman.
 * The ghosts switch between the two modes every 12 seconds. The first mode is always scatter.
 * When switching between the two modes, the ghosts make a 180 degree turn. (Otherwise not allowed)
 * This is implemented by the flip() method and chase variable.
 *
 * The game is won when all the dots are eaten.
 * The game is lost when the Pacman is eaten by a ghost.
 *
 * The ghosts are enabled one by one every 3 second passed, for easier gameplay.
 *
 * The game is updated by calling the update() method.
 *
 */
class Game {
    GameData* gd;
    bool chase = false;

    //The unit of movement for the entities
    const float MOVE_STEP = 0.1;

public:
    Game();
    ~Game();
    GameData* getInfo();

    //Update methods
    void update();
    void updatePacman();
    void updateGhosts();
    void updateStates();
    void flip();

    //Methods for Pacman
    bool checkIfCanTurn(Direction direction);
    void turn(Direction direction);
    bool checkIfCanMove(DynamicEntity* entity);
    void move(DynamicEntity* entity);
    void eat();

    //Methods for ghosts
    void turnGhost(Ghost* ghost);
    bool checkIfCanMoveGhost(Ghost* ghost);
    void moveGhost(Ghost* ghost);
    void setIfOutside(Ghost* ghost);
    void enableNext();

    //Methods for game states
    bool checkIfWon();
    bool checkIfDead();
};


#endif //PACMAN_GAME_HPP
