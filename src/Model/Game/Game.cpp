//
// Created by laccs on 4/7/2023.
//

#include "Game.hpp"
#include <fstream>
#include <cmath>
#include "../../System.hpp"
#include "../../View/Widget/Menu.hpp"
#include "../../Controller/Controller.hpp"
#include "../Entity/Ghost/Pinky.hpp"
#include "../Entity/Ghost/Inky.hpp"
#include "../Entity/Ghost/Clyde.hpp"

Game::Game() {
    //Initialize game data and entities
    gd = new GameData();
    gd->pacman = new Pacman();
    gd->ghosts[0] = new Blinky();
    gd->ghosts[1] = new Pinky(gd->pacman);
    gd->ghosts[2] = new Inky(gd->pacman, dynamic_cast<Blinky *>(gd->ghosts[0]));
    gd->ghosts[3] = new Clyde();

    //First ghost starts enabled
    gd->ghosts[0]->setEnabled(true);

    //Read and load map info
    std::ifstream mapFile("../assets/Map/pacman_map.txt");
    if (!mapFile.is_open()) {
        std::cout << "Failed to read map";
        exit(1);
    }

    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (auto &j: gd->map) {
            int x;
            mapFile >> x;

            if (x == PATH) {
                j[i] = PATH;
            } else if (x == WALL) {
                j[i] = WALL;
            } else if (x == DOT) {
                j[i] = DOT;
                gd->numberOfDots++; //Count number of dots
            } else if (x == GHOST_ONLY) {
                j[i] = GHOST_ONLY;
            }
        }
    }
}

Game::~Game() {
    delete gd;
}

GameData *Game::getInfo() {
    return gd;
}

//Update is broken down into smaller functions for readability
void Game::update() {
    updatePacman();
    updateGhosts();
    updateStates();
}

void Game::updatePacman() {
    move(gd->pacman);
    eat();
}

void Game::updateGhosts() {
    for (auto &ghost: gd->ghosts) {
        if (ghost->isEnabled()) {
            setIfOutside(ghost); //Check if ghost is outside of spawn area
            turnGhost(ghost); //Turn ghost if needed
            moveGhost(ghost); //Move ghost if possible
        }
    }
}

void Game::updateStates() {
    if (checkIfWon()) gd->gameWon = true;
    if (checkIfDead()) gd->gameOver = true;
}

//Switch between chase and scatter mode
void Game::flip() {
    chase = !chase;
    for (auto &ghost: gd->ghosts) {
        if (ghost->getDirection() == LEFT) {
            ghost->setDirection(RIGHT);
        } else if (ghost->getDirection() == RIGHT) {
            ghost->setDirection(LEFT);
        } else if (ghost->getDirection() == UP) {
            ghost->setDirection(DOWN);
        } else if (ghost->getDirection() == DOWN) {
            ghost->setDirection(UP);
        }
        ghost->setCooldown(1.0);
    }
}

bool Game::checkIfCanTurn(Direction direction) {
    //Check if Pacman is already moving in that direction
    if (direction == gd->pacman->getDirection()) return false;
    //Check if Pacman is in cooldown
    if (gd->pacman->getCooldown() < DynamicEntity::COOLDOWN) return false;

    //Code if we want to restrict Pacman and not allow 180 degree turns
    /*if ((direction == LEFT && gd->pacman->getDirection() == RIGHT) ||
        (direction == RIGHT && gd->pacman->getDirection() == LEFT) ||
        (direction == UP && gd->pacman->getDirection() == DOWN) ||
        (direction == DOWN && gd->pacman->getDirection() == UP)) {
        return false;
    }*/

    //Calculate rounded position for position checking
    float x = gd->pacman->getX();
    float y = gd->pacman->getY();
    int roundedX = (int) std::round(x);
    int roundedY = (int) std::round(y);

    //Check if there is a wall in the direction we want to turn
    if (direction == LEFT) {
        if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX - 1][roundedY] != WALL &&
            gd->map[roundedX][roundedY] != GHOST_ONLY && gd->map[roundedX - 1][roundedY] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == RIGHT) {
        if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX + 1][roundedY] != WALL &&
            gd->map[roundedX][roundedY] != GHOST_ONLY && gd->map[roundedX + 1][roundedY] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == UP) {
        if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX][roundedY - 1] != WALL &&
            gd->map[roundedX][roundedY] != GHOST_ONLY && gd->map[roundedX][roundedY - 1] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == DOWN) {
        if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX][roundedY + 1] != WALL &&
            gd->map[roundedX][roundedY] != GHOST_ONLY && gd->map[roundedX][roundedY + 1] != GHOST_ONLY) {
            return true;
        }
    }

    return false;
}

void Game::turn(Direction direction) {
    bool directionChanged = false;
    if (gd->pacman->getDirection() != direction) directionChanged = true;

    //If direction is changed, set new direction and reset cooldown
    //Also normalize position to not get stuck in walls
    if (directionChanged) {
        gd->pacman->setDirection(direction);
        gd->pacman->norm();
        gd->pacman->setCooldown(0.0);
    }

}

bool Game::checkIfCanMove(DynamicEntity *entity) {
    //Check if nearby tile is not a wall, neither a ghost only tile
    if (entity->getDirection() == LEFT &&
        gd->map[(int) std::round(entity->getX() - 0.5)][(int) std::round(entity->getY())] != WALL &&
        gd->map[(int) std::round(entity->getX() - 0.5)][(int) std::round(entity->getY())] != GHOST_ONLY) {
        return true;
    } else if (entity->getDirection() == RIGHT &&
               gd->map[(int) std::round(entity->getX() + 0.5)][(int) std::round(entity->getY())] != WALL &&
               gd->map[(int) std::round(entity->getX() + 0.5)][(int) std::round(entity->getY())] != GHOST_ONLY) {
        return true;
    } else if (entity->getDirection() == UP &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() - 0.5)] != WALL &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() - 0.5)] != GHOST_ONLY) {
        return true;
    } else if (entity->getDirection() == DOWN &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() + 0.5)] != WALL &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() + 0.5)] != GHOST_ONLY) {
        return true;
    }

    return false;
}

void Game::move(DynamicEntity *entity) {
    //Check if entity can move
    if (!checkIfCanMove(entity)) return;

    //Move entity
    if (entity->getDirection() == LEFT) {
        entity->move(-MOVE_STEP, 0);
        if (entity->getX() <= 0.0) entity->setX(28);
    } else if (entity->getDirection() == RIGHT) {
        entity->move(MOVE_STEP, 0);
        if (entity->getX() >= 28.0) entity->setX(0);
    } else if (entity->getDirection() == UP) {
        entity->move(0, -MOVE_STEP);
    } else if (entity->getDirection() == DOWN) {
        entity->move(0, MOVE_STEP);
    }
}

void Game::eat() {
    //Check if there is a dot in front of Pacman, if so, delete it
    if (gd->map[(int) std::round(gd->pacman->getX())][(int) std::round(gd->pacman->getY())] == DOT) {
        gd->map[(int) std::round(gd->pacman->getX())][(int) std::round(gd->pacman->getY())] = PATH;
        Controller::deleteDot((int) std::round(gd->pacman->getX()), (int) std::round(gd->pacman->getY()));
        --gd->numberOfDots;
    }
}

void Game::turnGhost(Ghost *ghost) {
    //Check if ghost is in cooldown
    if (ghost->getCooldown() < DynamicEntity::COOLDOWN) return;

    //Calculate rounded position
    float x = ghost->getX();
    float y = ghost->getY();
    int roundedX = (int) std::round(x);
    int roundedY = (int) std::round(y);

    //Calculate possible directions using bitwise operations
    int neighbour = 0;
    if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX - 1][roundedY] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX - 1][roundedY] != GHOST_ONLY) {
                neighbour += LEFT;
            }
        } else {
            neighbour += LEFT;
        }
    }
    if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX + 1][roundedY] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX + 1][roundedY] != GHOST_ONLY) {
                neighbour += RIGHT;
            }
        } else {
            neighbour += RIGHT;
        }
    }
    if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX][roundedY - 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX][roundedY - 1] != GHOST_ONLY) {
                neighbour += UP;
            }
        } else {
            neighbour += UP;
        }
    }
    if (gd->map[roundedX][roundedY] != WALL && gd->map[roundedX][roundedY + 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX][roundedY + 1] != GHOST_ONLY) {
                neighbour += DOWN;
            }
        } else {
            neighbour += DOWN;
        }
    }

    //Calculate target and path
    ghost->calculateTarget(gd->pacman->getX(), gd->pacman->getY(), this->chase);
    Direction direction = ghost->calculatePath(neighbour);

    //If there is no path, return. This case is triggered when the ghost is in a dead end (should never happen) or when the ghost is in a tunnel
    if (direction == 0) return;

    //180 degree turn check
    if ((direction == LEFT && ghost->getDirection() == RIGHT) ||
        (direction == RIGHT && ghost->getDirection() == LEFT) ||
        (direction == UP && ghost->getDirection() == DOWN) ||
        (direction == DOWN && ghost->getDirection() == UP)) {
        return;
    }

    bool directionChanged = false;
    if (ghost->getDirection() != direction) directionChanged = true;

    //If direction changed, set new direction and cooldown, also normalize the ghost's position
    if (directionChanged) {
        ghost->setDirection(direction);
        ghost->norm();
        ghost->setCooldown(0.0);
    }
}

bool Game::checkIfCanMoveGhost(Ghost *ghost) {
    //Calculate rounded position
    float x = ghost->getX();
    float y = ghost->getY();
    int roundedX = (int) std::round(x);
    int roundedY = (int) std::round(y);

    //Check if ghost is in a tunnel
    if (roundedX == 0 || roundedX == -1 || roundedX == 28 || roundedX == 29) return true;

    //Check if ghost can move in its current direction
    //Ghost only areas included
    if (ghost->getDirection() == LEFT && gd->map[roundedX - 1][roundedY] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX - 1][roundedY] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == RIGHT && gd->map[roundedX + 1][roundedY] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX + 1][roundedY] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == UP && gd->map[roundedX][roundedY - 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX][roundedY - 1] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == DOWN && gd->map[roundedX][roundedY + 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[roundedX][roundedY + 1] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    }

    return false;
}

void Game::moveGhost(Ghost *ghost) {
    //Check if ghost is in cooldown
    if (!checkIfCanMoveGhost(ghost)) return;

    //If ghost is in a tunnel, teleport it to the other side
    if (ghost->getX() <= 0) ghost->setX(26.7);
    else if (ghost->getX() >= 27) ghost->setX(0.3);

    //Move ghost
    if (ghost->getDirection() == LEFT) {
        ghost->move(-MOVE_STEP, 0);
    } else if (ghost->getDirection() == RIGHT) {
        ghost->move(MOVE_STEP, 0);
    } else if (ghost->getDirection() == UP) {
        ghost->move(0, -MOVE_STEP);
    } else if (ghost->getDirection() == DOWN) {
        ghost->move(0, MOVE_STEP);
    }
}

void Game::setIfOutside(Ghost *ghost) {
    //Calculate rounded position
    float x = ghost->getX();
    float y = ghost->getY();
    int roundedX = (int) std::round(x);
    int roundedY = (int) std::round(y);

    //Check if ghost is in spawn area
    if (gd->map[roundedX][roundedY] != GHOST_ONLY) {
        ghost->setIsOutside(true);
    } else {
        ghost->setIsOutside(false);
    }
}

bool Game::checkIfWon() {
    //Check if all dots are eaten
    return gd->numberOfDots == 0;
}

bool Game::checkIfDead() {
    //Check if pacman is dead by checking if it collides with any of the ghosts
    for (auto &ghost: gd->ghosts) {
        if (Entity::checkCollision(gd->pacman, ghost)) return true;
    }
    return false;
}

void Game::enableNext() {
    //Check if all ghosts are enabled
    if (gd->enabled == GameData::NUMBER_OF_GHOSTS) return;

    //Enable next ghost
    gd->ghosts[gd->enabled]->setEnabled(true);
    gd->enabled++;
}