//
// Created by csong on 4/7/2023.
//

#include "Controller.hpp"
#include "../Model/Game.hpp"
#include "../View/Widget/Menu.hpp"

Game* Controller::game{};
GameMenu* Controller::gameMenu{};
GameData* Controller::gd{};

Controller::Controller() = default;

void Controller::init(Game* _game, GameMenu* _gameMenu) {
    Controller::game = _game;
    Controller::gameMenu = _gameMenu;
    Controller::gd = _game->getInfo();
}

void Controller::getInfo() {
    gd = game->getInfo();
}

void Controller::sendInfo() {
    gameMenu->setInfo(gd);
}

bool Controller::askIfCanTurn(Direction direction) {
    return game->checkIfCanTurn(direction);
}

void Controller::turn(Direction direction) {
    game->turn(direction);
}

void Controller::deleteDot(int j, int i) {
    gameMenu->removeDot(j,i);
}
