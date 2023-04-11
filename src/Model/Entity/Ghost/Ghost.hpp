//
// Created by laccs on 4/9/2023.
//

#ifndef PACMAN_GHOST_HPP
#define PACMAN_GHOST_HPP

#include "../Core/DynamicEntity.hpp"

/**
 * The Ghost class is the base class for all ghosts, each ghost has a target, the calculation of which is different for each ghost
 * The target is the point the ghost is trying to reach.
 * The enabled flag is used to tell if the ghost is currently active or not.
 * The isOutside flag is used to tell if the ghost is outside the cage or not.
 * The calculatePath method is used to calculate the next direction the ghost should take.
 *
 * When calculation the path, meaning the next direction the ghost should take, we look at the neighbouring cells.
 * The neighbour parameter is a number that tells us which cells are empty, meaning they are paths.
 * The number is a bit mask, each bit represents a direction.
 * 1 - up
 * 2 - right
 * 4 - down
 * 8 - left
 * The number is calculated by adding the values of the directions that are free.
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

    bool enabled = false;
    bool isOutside = false;

public:
    Ghost();

    virtual void calculateTarget(float x, float y, bool chase) = 0;

    Direction calculatePath(int neighbour);

    bool isEnabled() const;

    void setEnabled(bool _enabled);

    void setIsOutside(bool _isOutside);

    bool getIsOutside() const;
};

#endif //PACMAN_GHOST_HPP
