//
// Created by csong on 4/9/2023.
//

#ifndef PACMAN_GHOST_HPP
#define PACMAN_GHOST_HPP

#include "DynamicEntity.hpp"

/**
 * The neighbour parameter serves to tell how many neighbouring empty cells, meaning paths are adjacent to the current ghost
 * We look at the four bits of the number, each will tell one direction
 * 1 - up
 * 2 - right
 * 4 - down
 * 8 - left
 *
 * Meaning:
 * 0 - no free cell
 * 1 - up free
 * 2 - right free
 * 3 - up and right free
 * 4 - down free
 * 5 - up and down free
 * 6 - right and down free
 * 7 - up, right and down free
 * 8 - left free
 * 9 - left and up free
 * ...and so on
 */

class Ghost : public DynamicEntity {
protected:
    struct Target {
        float x;
        float y;
    } target{};

    bool isOutside = false;

public:
    Ghost();
    virtual void calculateTarget(float x, float y) = 0;
    Direction calculatePath(int neighbour);
    void setIsOutside(bool isOutside);
    bool getIsOutside() const;
};


#endif //PACMAN_GHOST_HPP
