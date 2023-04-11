//
// Created by laccs on 4/8/2023.
//

#ifndef PACMAN_DYNAMICENTITY_HPP
#define PACMAN_DYNAMICENTITY_HPP

#include "Entity.hpp"
#include "../../../Enums.hpp"

/**
 * A dynamic entity is an entity that can move
 * It has a direction and a cooldown, which is the distance that must be travelled after turning again
 * The cooldown is used to prevent the entity from turning too often, which would cause it to turn back and forth
 * The static COOLDOWN is the threshold for the cooldown
 */
class DynamicEntity : public Entity {
protected:
    Direction direction{};
    float cooldown = 2;

public:
    static float COOLDOWN;

    void move(float x, float y);

    //Rounds the position to the nearest integer, since the position is stored as a float
    //Used when an entity is turning and the position is not an integer, which would cause it to move into a wall
    void norm();

    Direction getDirection() const;

    void setDirection(Direction direction);

    float getCooldown() const;

    void setCooldown(float cooldown);
};


#endif //PACMAN_DYNAMICENTITY_HPP
