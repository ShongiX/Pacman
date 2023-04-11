//
// Created by laccs on 4/10/2023.
//

#include "Pinky.hpp"
#include "../Pacman/Pacman.hpp"

Pinky::Pinky(Pacman* pacman) {
    //Initial position and direction
    this->x = 13;
    this->y = 17;

    this->direction = RIGHT;

    //Has a reference to the pacman to get its direction
    this->pacman = pacman;

    //Initial target outside of the spawn box
    target.x = 12;
    target.y = 14;
}

void Pinky::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            //Based on Pacman's direction, the target is 4 tiles in front of him
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
            //In scatter mode, the target is the top left corner
            target.x = 2;
            target.y = -1;
        }
    } else {
        //If still in the spawn box, the target is just outside the box
        target.x = 12;
        target.y = 14;
    }
}
