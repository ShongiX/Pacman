//
// Created by laccs on 4/10/2023.
//

#ifndef PACMAN_INKY_HPP
#define PACMAN_INKY_HPP

#include "Ghost.hpp"

class Pacman;
class Blinky;

class Inky : public Ghost {
private:
    Pacman* pacman{};
    Blinky* blinky{};
public:
    Inky(Pacman* pacman, Blinky* blinky);

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_INKY_HPP
