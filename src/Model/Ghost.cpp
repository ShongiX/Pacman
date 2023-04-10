//
// Created by csong on 4/9/2023.
//

#include "Ghost.hpp"
#include <cmath>

Ghost::Ghost() : DynamicEntity() {}

Direction Ghost::calculatePath(int neighbour) {
    float minDist = 9999;
    int result = 0;

    if (neighbour & UP) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y - 1 - target.y) * (y - 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = UP;
        }
    }
    if (neighbour & RIGHT) {
        float dist = std::sqrt((x + 1 - target.x) * (x + 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = RIGHT;
        }
    }
    if (neighbour & DOWN) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y + 1 - target.y) * (y + 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = DOWN;
        }
    }
    if (neighbour & LEFT) {
        float dist = std::sqrt((x - 1 - target.x) * (x - 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            result = LEFT;
        }
    }



    return static_cast<Direction>(result);
}
