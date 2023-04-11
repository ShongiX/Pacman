//
// Created by laccs on 4/10/2023.
//

#include "Clyde.hpp"
#include <cmath>

Clyde::Clyde() {
    //Initial position and direction
    this->x = 15.25;
    this->y = 17;

    this->direction = LEFT;

    //Initial target outside of the spawn box
    target.x = 15;
    target.y = 14;
}

void Clyde::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            //If the distance is greater than 8 tiles, go to Pacman's position
            if (std::sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y)) > 8) {
                target.x = x;
                target.y = y;
            } else {
                //Otherwise, go to the bottom left corner
                target.x = 0;
                target.y = 34;
            }
        } else {
            //In scatter mode, go to the bottom left corner
            target.x = 0;
            target.y = 34;
        }
    } else {
        //If still in the spawn box, the target is just outside the box
        target.x = 15;
        target.y = 14;
    }
}

