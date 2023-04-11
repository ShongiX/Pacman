//
// Created by laccs on 4/10/2023.
//

#ifndef PACMAN_CLYDE_HPP
#define PACMAN_CLYDE_HPP

#include "Ghost.hpp"


/**
 * Clyde is the orange ghost. Its target is Pacman's position if the distance is greater than 8 tiles, otherwise it goes to the bottom left corner.
 * If in scatter mode, it goes to the bottom left corner.
 * If still in the spawn box, the target is just outside the box.
 */
class Clyde : public Ghost {
public:
    Clyde();

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_CLYDE_HPP
