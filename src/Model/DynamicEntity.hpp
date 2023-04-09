//
// Created by csong on 4/8/2023.
//

#ifndef PACMAN_DYNAMICENTITY_HPP
#define PACMAN_DYNAMICENTITY_HPP

#include "Entity.hpp"
#include "../Enums.hpp"

class DynamicEntity : public Entity {
protected:
    Direction direction;

public:
    Direction getDirection() const;
    void setDirection(Direction direction);

    void move(float x, float y);
    void norm();
};


#endif //PACMAN_DYNAMICENTITY_HPP
