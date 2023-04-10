//
// Created by csong on 4/10/2023.
//

#include "Inky.hpp"
#include "Blinky.hpp"
#include "../Pacman/Pacman.hpp"

Inky::Inky(Pacman *pacman, Blinky *blinky) {
    this->x = 15;
    this->y = 17;

    this->pacman = pacman;
    this->blinky = blinky;

    this->direction = RIGHT;

    //initial target outside of the spawn box
    target.x = 15;
    target.y = 14;
}

void Inky::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            float px, py; //2 tiles ahead of pacman
            float bx, by; //blinky exact position

            if (pacman->getDirection() == LEFT) {
                px = x - 2;
                py = y;
            } else if (pacman->getDirection() == RIGHT) {
                px = x + 2;
                py = y;
            } else if (pacman->getDirection() == UP) {
                px = x;
                py = y - 2;
            } else {
                px = x;
                py = y + 2;
            }

            bx = blinky->getX();
            by = blinky->getY();

            float dx, dy;
            dx = bx - px;
            dy = by - py;

            target.x = x - dx;
            target.y = y - dy;
        } else {
            target.x = 27;
            target.y = 34;
        }
    } else {
        target.x = 15;
        target.y = 14;
    }
}
