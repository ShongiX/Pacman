//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_ENUMS_HPP
#define PACMAN_ENUMS_HPP

enum State {
    MAIN, PLAY, WIN, DEAD
};
enum Tile {
    PATH, WALL, DOT, GHOST_ONLY
};
enum Direction {
    UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8
};

#endif //PACMAN_ENUMS_HPP
