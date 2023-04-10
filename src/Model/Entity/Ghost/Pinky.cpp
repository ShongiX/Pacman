//
// Created by csong on 4/10/2023.
//

#include "Pinky.hpp"
#include "../Pacman.hpp"

Pinky::Pinky(Pacman* pacman) {
    this->x = 13;
    this->y = 17;

    this->pacman = pacman;

    this->direction = LEFT;

    //initial target outside of the spawn box
    target.x = 12;
    target.y = 14;
}

void Pinky::calculateTarget(float x, float y) {
    if (isOutside) {
        if (pacman->getDirection() == LEFT) {
            target.x = x - 4;
            target.y = y;
        } else if (pacman->getDirection() == RIGHT) {
            target.x = x + 4;
            target.y = y;
        } else if (pacman->getDirection() == UP) {
            target.x = x;
            target.y = y - 4;
        } else if (pacman->getDirection() == DOWN) {
            target.x = x;
            target.y = y + 4;
        }
    } else {
        target.x = 12;
        target.y = 14;
    }
}
