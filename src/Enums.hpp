//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_ENUMS_HPP
#define PACMAN_ENUMS_HPP

/**
 * @brief Enumerations used in the game
 */
enum State {
    MAIN, PLAY, WIN, DEAD
};
enum Tile {
    PATH, WALL, DOT, GHOST_ONLY
};
enum Direction {
    //The values are powers of 2 so that they can be used as bitmasks
    UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8
};

#endif //PACMAN_ENUMS_HPP
