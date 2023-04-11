//
// Created by csong on 4/7/2023.
//

#ifndef PACMAN_CONTROLLER_HPP
#define PACMAN_CONTROLLER_HPP

#include "../Enums.hpp"

class Game;
class GameMenu;
class GameData;

class Controller {
    static Game *game;
    static GameMenu *gameMenu;
    static GameData *gd;

public:
    Controller();

    static void init(Game *_game, GameMenu *_gameMenu);

    static void getInfo();
    static void sendInfo();

    static bool askIfCanTurn(Direction direction);
    static void turn(Direction direction);

    static void deleteDot(int j, int i);

    static void flip();
    static void enableNext();
};

#endif //PACMAN_CONTROLLER_HPP
