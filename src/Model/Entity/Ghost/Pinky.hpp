//
// Created by csong on 4/10/2023.
//

#ifndef PACMAN_PINKY_HPP
#define PACMAN_PINKY_HPP

#include "Ghost.hpp"

class Pacman;

class Pinky : public Ghost {
private:
    Pacman* pacman{};
public:
    Pinky(Pacman* pacman);

    void calculateTarget(float x, float y, bool chase) override;
};


#endif //PACMAN_PINKY_HPP
