//
// Created by csong on 4/9/2023.
//

#include "Blinky.hpp"

Blinky::Blinky() : Ghost() {
    this->x = 12;
    this->y = 17;
}

void Blinky::calculateTarget(float x, float y) {
    target.x = x;
    target.y = y;
}



