//
// Created by laccs on 4/8/2023.
//

#include "Entity.hpp"

// Meaning that if two entities are closer than 0.7 units, they are considered to be colliding
float Entity::COLLISION_TRESHOLD = 0.7;

float Entity::getX() const {
    return x;
}

void Entity::setX(float _x) {
    Entity::x = _x;
}

float Entity::getY() const {
    return y;
}

bool Entity::checkCollision(Entity *a, Entity *b) {
    if ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) < COLLISION_TRESHOLD) {
        return true;
    }
    return false;
}
