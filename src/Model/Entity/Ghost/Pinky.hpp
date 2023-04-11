//
// Created by laccs on 4/10/2023.
//

#ifndef PACMAN_PINKY_HPP
#define PACMAN_PINKY_HPP

#include "Ghost.hpp"

/**
 * Pinky is the pink ghost. Its target is 4 tiles in front of Pacman.
 * If in scatter mode, it goes to the top left corner.
 * If still in the spawn box, the target is just outside the box.
 */
class Pacman;

class Pinky : public Ghost {
private:
    Pacman *pacman{};
public:
    explicit Pinky(Pacman *pacman);

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_PINKY_HPP
