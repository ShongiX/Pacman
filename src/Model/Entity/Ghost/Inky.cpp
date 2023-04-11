//
// Created by laccs on 4/10/2023.
//

#include "Inky.hpp"
#include "Blinky.hpp"
#include "../Pacman/Pacman.hpp"

Inky::Inky(Pacman *pacman, Blinky *blinky) {
    //Initial position and direction
    this->x = 14;
    this->y = 17;

    this->direction = LEFT;

    //Has a reference to Pacman and Blinky for target calculation
    this->pacman = pacman;
    this->blinky = blinky;

    //Initial target outside of the spawn box
    target.x = 15;
    target.y = 14;
}

void Inky::calculateTarget(float x, float y, bool chase) {
    if (isOutside) {
        if (chase) {
            float px, py; //2 tiles ahead of pacman
            float bx, by; //Blinky exact position

            //Calculate necessary values based on Pacman's direction
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

            //Calculate the mirrored position
            float dx, dy;
            dx = bx - px;
            dy = by - py;

            target.x = x - dx;
            target.y = y - dy;
        } else {
            //In scatter mode, go to the bottom right corner
            target.x = 27;
            target.y = 34;
        }
    } else {
        //If still in the spawn box, the target is just outside the box
        target.x = 15;
        target.y = 14;
    }
}
