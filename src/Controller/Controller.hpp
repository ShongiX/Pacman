//
// Created by laccs on 4/7/2023.
//

#ifndef PACMAN_CONTROLLER_HPP
#define PACMAN_CONTROLLER_HPP

#include "../Enums.hpp"

class Game;
class GameMenu;
class GameData;

/**
 * This class is the Controller from the MVC model. It transfers data between the View (Menu) and the Model (Game)
 * with the help of the GameData class, which includes all important info about the state of the game.
 *
 * This class provides an interface through the Menu and Game classes can exchange data and call each other's functions
 * if a certain trigger is activated.
 *
 * The class keeps a pointer to the instances of Menu and Game to know who to forward a received message
 * and who to call a function from.
 *
 * The class is static, so it can be accessed without creating an instance of it.
 */
class Controller {
    static Game *game;
    static GameMenu *gameMenu;
    static GameData *gd;

public:
    Controller();

    // Function to initialize the Controller
    static void init(Game *_game, GameMenu *_gameMenu);

    // Getters and setters for the GameData
    static void getInfo();
    static void sendInfo();

    // Functions to call the Game class
    static bool askIfCanTurn(Direction direction);
    static void turn(Direction direction);
    static void flip();
    static void enableNext();

    // Functions to call the Menu class
    static void deleteDot(int j, int i);
};

#endif //PACMAN_CONTROLLER_HPP
