//
// Created by laccs on 4/9/2023.
//

#include "Blinky.hpp"

Blinky::Blinky() : Ghost() {
    //Initial position and direction
    this->x = 11.75;
    this->y = 17;

    this->direction = RIGHT;

    //Initial target outside of the spawn box
    target.x = 12;
    target.y = 14;
}

void Blinky::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        //If in chase mode, the target is the player's position
        if (chase) {
            target.x = x;
            target.y = y;
        } else {
            //If in scatter mode, the target is the top right corner
            target.x = 33;
            target.y = -1;
        }
    } else {
        //If still in the spawn box, the target is just outside the box
        target.x = 12;
        target.y = 14;
    }
}



