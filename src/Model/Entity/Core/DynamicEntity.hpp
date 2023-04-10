//
// Created by csong on 4/8/2023.
//

#ifndef PACMAN_DYNAMICENTITY_HPP
#define PACMAN_DYNAMICENTITY_HPP

#include "Entity.hpp"
#include "../../../Enums.hpp"

class DynamicEntity : public Entity {
protected:
    Direction direction;
    float cooldown = 2;

public:
    static float COOLDOWN;

    Direction getDirection() const;
    void setDirection(Direction direction);

    void move(float x, float y);
    void norm();

    float getCooldown() const;
    void setCooldown(float cooldown);
};


#endif //PACMAN_DYNAMICENTITY_HPP
