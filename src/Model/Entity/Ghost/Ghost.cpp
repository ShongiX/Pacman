//
// Created by laccs on 4/9/2023.
//

#include "Ghost.hpp"
#include <cmath>
#include <iostream>

Ghost::Ghost() : DynamicEntity() {}

Direction Ghost::calculatePath(int neighbour) {
    float minDist = 9999;
    int result = 0;

    //std::cout << "Current direction: " << direction << "  Calc path: ";

    if (neighbour & UP && direction != DOWN) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y - 1 - target.y) * (y - 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = UP;
        }
        //std::cout << "up: " << dist << ", ";
    }
    if (neighbour & RIGHT && direction != LEFT) {
        float dist = std::sqrt((x + 1 - target.x) * (x + 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = RIGHT;
        }
        //std::cout << "right: " << dist << ", ";
    }
    if (neighbour & DOWN && direction != UP) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y + 1 - target.y) * (y + 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = DOWN;
        }
        //std::cout << "down: " << dist << ", ";
    }
    if (neighbour & LEFT && direction != RIGHT) {
        float dist = std::sqrt((x - 1 - target.x) * (x - 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            result = LEFT;
        }
        //std::cout << "left: " << dist << ", ";
    }

    //std::cout << "choice: " << result << "\n";


    return static_cast<Direction>(result);
}

bool Ghost::isEnabled() const {
    return enabled;
}

void Ghost::setEnabled(bool enabled) {
    Ghost::enabled = enabled;
}

void Ghost::setIsOutside(bool isOutside) {
    this->isOutside = isOutside;
}

bool Ghost::getIsOutside() const {
    return isOutside;
}
