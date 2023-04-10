//
// Created by csong on 4/10/2023.
//

#ifndef PACMAN_CLYDE_HPP
#define PACMAN_CLYDE_HPP


#include "Ghost.hpp"

class Clyde : public Ghost {
public:
    Clyde();

    void calculateTarget(float x, float y) override;
};


#endif //PACMAN_CLYDE_HPP
