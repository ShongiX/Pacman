//
// Created by laccs on 4/9/2023.
//

#ifndef PACMAN_BLINKY_HPP
#define PACMAN_BLINKY_HPP

#include "Ghost.hpp"

/**
 * Blinky is the red ghost. It chases the player directly, meaning its target is the player's position.
 * If in scatter mode, it goes to the top right corner.
 * If still in the spawn box, the target is just outside the box.
 */
class Blinky : public Ghost {

public:
    Blinky();

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_BLINKY_HPP
