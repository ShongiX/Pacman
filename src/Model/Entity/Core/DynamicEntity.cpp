//
// Created by csong on 4/8/2023.
//

#include <cmath>
#include "DynamicEntity.hpp"


void DynamicEntity::move(float x, float y) {
    this->x += x;
    this->y += y;
}

Direction DynamicEntity::getDirection() const {
    return direction;
}

void DynamicEntity::setDirection(Direction direction) {
    DynamicEntity::direction = direction;
}

void DynamicEntity::norm() {
    this->x = std::round(x);
    this->y = std::round(y);

    /*if (direction == LEFT) {
        this->x = std::ceil(x);
        this->y = std::round(y);
    } else if (direction == RIGHT) {
        this->x = std::floor(x);
        this->y = std::round(y);
    } else if (direction == UP) {
        this->x = std::round(x);
        this->y = std::ceil(y);
    } else if (direction == DOWN) {
        this->x = std::round(x);
        this->y = std::floor(y);
    }*/
}
