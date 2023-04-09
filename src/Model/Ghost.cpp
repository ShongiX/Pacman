//
// Created by csong on 4/9/2023.
//

#include "Ghost.hpp"
#include <cmath>

int Ghost::up = 1;
int Ghost::right = 2;
int Ghost::down = 4;
int Ghost::left = 8;

Ghost::Ghost() : DynamicEntity() {}

int Ghost::calculatePath(int neighbour) {
    float minDist = 9999;
    int result = 0;

    if (neighbour & up) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y - 1 - target.y) * (y - 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = up;
        }
    }
    if (neighbour & right) {
        float dist = std::sqrt((x + 1 - target.x) * (x + 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = right;
        }
    }
    if (neighbour & down) {
        float dist = std::sqrt((x - target.x) * (x - target.x) + (y + 1 - target.y) * (y + 1 - target.y));
        if (dist < minDist) {
            minDist = dist;
            result = down;
        }
    }
    if (neighbour & left) {
        float dist = std::sqrt((x - 1 - target.x) * (x - 1 - target.x) + (y - target.y) * (y - target.y));
        if (dist < minDist) {
            result = left;
        }
    }

    return result;
}
