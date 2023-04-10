//
// Created by csong on 4/10/2023.
//

#include "Clyde.hpp"
#include <cmath>

Clyde::Clyde() {
    this->x = 15;
    this->y = 17;

    this->direction = LEFT;

    //initial target outside of the spawn box
    target.x = 15;
    target.y = 14;
}

void Clyde::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            if (std::sqrt(  (this->x - x)*(this->x - x) + (this->y - y)*(this->y - y)   ) > 8 ) {
                target.x = x;
                target.y = y;
            } else {
                target.x = 0;
                target.y = 34;
            }
        } else {
            target.x = 0;
            target.y = 34;
        }
    } else {
        target.x = 15;
        target.y = 14;
    }
}

