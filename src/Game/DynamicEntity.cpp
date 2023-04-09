//
// Created by csong on 4/8/2023.
//

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
