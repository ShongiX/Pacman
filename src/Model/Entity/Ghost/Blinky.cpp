//
// Created by laccs on 4/9/2023.
//

#include "Blinky.hpp"

Blinky::Blinky() : Ghost() {
    this->x = 11.75;
    this->y = 17;

    this->direction = RIGHT;

    //initial target outside of the spawn box
    target.x = 12;
    target.y = 14;
}

void Blinky::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            target.x = x;
            target.y = y;
        } else {
            target.x = 33;
            target.y = -1;
        }
    } else {
        target.x = 12;
        target.y = 14;
    }
}



