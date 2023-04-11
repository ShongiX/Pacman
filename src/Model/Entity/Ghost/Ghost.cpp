//
// Created by laccs on 4/9/2023.
//

#include "Ghost.hpp"
#include <cmath>

Ghost::Ghost() : DynamicEntity() {}

Direction Ghost::calculatePath(int neighbour) {
    //The minimum distance is initialized to a very large number
    float minDist = 9999;

    //The result is initialized to 0, meaning no direction
    int result = 0;

    //We check each direction, if the direction is free and it is not the opposite of the current direction, we calculate the distance to the target
    //If the distance is smaller than the minimum distance, we update the minimum distance and the result
    if (neighbour & UP && direction != DOWN) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y - 1 - target.y) * (y - 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = UP;
        }
    }
    if (neighbour & RIGHT && direction != LEFT) {
        float dist = std::sqrt((x + 1 - target.x) * (x + 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = RIGHT;
        }
    }
    if (neighbour & DOWN && direction != UP) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y + 1 - target.y) * (y + 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = DOWN;
        }
    }
    if (neighbour & LEFT && direction != RIGHT) {
        float dist = std::sqrt((x - 1 - target.x) * (x - 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            result = LEFT;
        }
    }

    //We return the result as a Direction
    return static_cast<Direction>(result);
}

bool Ghost::isEnabled() const {
    return enabled;
}

void Ghost::setEnabled(bool _enabled) {
    Ghost::enabled = _enabled;
}

void Ghost::setIsOutside(bool _isOutside) {
    this->isOutside = _isOutside;
}

bool Ghost::getIsOutside() const {
    return isOutside;
}
