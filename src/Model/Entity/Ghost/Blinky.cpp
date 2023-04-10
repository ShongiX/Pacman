//
// Created by csong on 4/9/2023.
//

#include "Blinky.hpp"

Blinky::Blinky() : Ghost() {
    this->x = 12;
    this->y = 17;

    this->direction = LEFT;

    //initial target outside of the spawn box
    target.x = 12;
    target.y = 14;
}

void Blinky::calculateTarget(float x, float y) {
    if (isOutside) {
        target.x = x;
        target.y = y;
    } else {
        target.x = 12;
        target.y = 14;
    }
}



