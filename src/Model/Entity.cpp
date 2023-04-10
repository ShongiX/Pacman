//
// Created by csong on 4/8/2023.
//

#include "Entity.hpp"
float Entity::COLLISION_TRESHOLD = 0.7;

float Entity::getX() const {
    return x;
}

void Entity::setX(float x) {
    Entity::x = x;
}

float Entity::getY() const {
    return y;
}

void Entity::setY(float y) {
    Entity::y = y;
}

bool Entity::checkCollision(Entity* a, Entity* b) {
    if ((a->x - b->x) * (a->x - b->x) + (a->y - b->y)*(a->y - b->y) < COLLISION_TRESHOLD) {
        return true;
    }
    return false;
}
