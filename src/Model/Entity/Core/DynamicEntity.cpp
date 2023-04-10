//
// Created by csong on 4/8/2023.
//

#include <cmath>
#include "DynamicEntity.hpp"

//The distance that must be travelled after turning again
float DynamicEntity::COOLDOWN = 1.0;

void DynamicEntity::move(float x, float y) {
    this->x += x;
    this->y += y;
    cooldown += (std::sqrt(x*x+y*y));
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
}

float DynamicEntity::getCooldown() const {
    return cooldown;
}

void DynamicEntity::setCooldown(float cooldown) {
    DynamicEntity::cooldown = cooldown;
}
