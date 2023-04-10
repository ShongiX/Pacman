//
// Created by csong on 4/9/2023.
//

#ifndef PACMAN_BLINKY_HPP
#define PACMAN_BLINKY_HPP

#include "Ghost.hpp"

class Blinky : public Ghost {

public:
    Blinky();

    void calculateTarget(float x, float y) override;
};


#endif //PACMAN_BLINKY_HPP
