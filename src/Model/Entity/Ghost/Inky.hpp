//
// Created by laccs on 4/10/2023.
//

#ifndef PACMAN_INKY_HPP
#define PACMAN_INKY_HPP

#include "Ghost.hpp"

class Pacman;
class Blinky;

/**
 * Inky is the cyan ghost. Its target is mirrored from Blinky's position to Pacman's position (2 tiles ahead).
 * If in scatter mode, it goes to the bottom right corner.
 * If still in the spawn box, the target is just outside the box.
 */
class Inky : public Ghost {
private:
    Pacman* pacman{};
    Blinky* blinky{};
public:
    Inky(Pacman* pacman, Blinky* blinky);

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_INKY_HPP
