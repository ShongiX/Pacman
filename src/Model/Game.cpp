//
// Created by csong on 4/7/2023.
//

#include "../System.hpp"
#include <fstream>
#include <cmath>
#include "Game.hpp"
#include "../View/Widget/Menu.hpp"
#include "../Controller/Controller.hpp"
#include "Entity/Ghost/Pinky.hpp"
#include "Entity/Ghost/Inky.hpp"
#include "Entity/Ghost/Clyde.hpp"


Game::Game() {
    gd = new GameData();
    gd->pacman = new Pacman();
    gd->ghosts[0] = new Blinky();
    gd->ghosts[1] = new Pinky(gd->pacman);
    gd->ghosts[2] = new Inky(gd->pacman, dynamic_cast<Blinky *>(gd->ghosts[0]));
    gd->ghosts[3] = new Clyde();

    gd->ghosts[0]->setEnabled(true);

    //Read and load map info
    std::ifstream mapFile("../assets/pacman_map.txt");
    if (!mapFile.is_open()) {
        std::cout << "Failed to read map";
        exit(1);
    }
    for (int i = 0; i < GameData::MAP_HEIGHT; ++i) {
        for (int j = 0; j < GameData::MAP_WIDTH; ++j) {
            int x;
            mapFile >> x;

            if (x == PATH) {
                gd->map[j][i] = PATH;
            } else if (x == WALL) {
                gd->map[j][i] = WALL;
            } else if (x == DOT) {
                gd->map[j][i] = DOT;
            } else if (x == GHOST_ONLY) {
                gd->map[j][i] = GHOST_ONLY;
            }
        }
    }
}

GameData *Game::getInfo() {
    return gd;
}

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
            setIfOutside(ghost);
            turnGhost(ghost);
            moveGhost(ghost);
        }
    }
}

void Game::updateStates() {
    if (checkIfWon()) gd->gameWon = true;
    if (checkIfDead()) gd->gameOver = true;
}

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
    if (direction == gd->pacman->getDirection()) return false;
    if (gd->pacman->getCooldown() < DynamicEntity::COOLDOWN) return false;
    //Code if we want to restrict Pacman from 180 degree turns
    /*if ((direction == LEFT && gd->pacman->getDirection() == RIGHT) ||
        (direction == RIGHT && gd->pacman->getDirection() == LEFT) ||
        (direction == UP && gd->pacman->getDirection() == DOWN) ||
        (direction == DOWN && gd->pacman->getDirection() == UP)) {
        return false;
    }*/

    float x = gd->pacman->getX();
    float y = gd->pacman->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);
    if (direction == LEFT) {
        if (gd->map[r][c] != WALL && gd->map[r - 1][c] != WALL &&
            gd->map[r][c] != GHOST_ONLY && gd->map[r - 1][c] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == RIGHT) {
        if (gd->map[r][c] != WALL && gd->map[r + 1][c] != WALL &&
            gd->map[r][c] != GHOST_ONLY && gd->map[r + 1][c] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == UP) {
        if (gd->map[r][c] != WALL && gd->map[r][c - 1] != WALL &&
            gd->map[r][c] != GHOST_ONLY && gd->map[r][c - 1] != GHOST_ONLY) {
            return true;
        }
    } else if (direction == DOWN) {
        if (gd->map[r][c] != WALL && gd->map[r][c + 1] != WALL &&
            gd->map[r][c] != GHOST_ONLY && gd->map[r][c + 1] != GHOST_ONLY) {
            return true;
        }
    }

    return false;
}

void Game::turn(Direction direction) {
    bool directionChanged = false;
    if (gd->pacman->getDirection() != direction) directionChanged = true;

    if (directionChanged) {
        gd->pacman->setDirection(direction);
        gd->pacman->norm();
        gd->pacman->setCooldown(0.0);
    }

}

bool Game::checkIfCanMove(DynamicEntity *entity) {
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
    if (!checkIfCanMove(entity)) return;

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
    if (gd->map[(int) std::round(gd->pacman->getX())][(int) std::round(gd->pacman->getY())] == DOT) {
        gd->map[(int) std::round(gd->pacman->getX())][(int) std::round(gd->pacman->getY())] = PATH;
        Controller::deleteDot((int) std::round(gd->pacman->getX()), (int) std::round(gd->pacman->getY()));
        --gd->numberOfDots;
    }
}

void Game::turnGhost(Ghost *ghost) {
    if (ghost->getCooldown() < DynamicEntity::COOLDOWN) return;

    float x = ghost->getX();
    float y = ghost->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);

    int neighbour = 0;

    if (gd->map[r - 1][c] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r - 1][c] != GHOST_ONLY) {
                neighbour += LEFT;
            }
        } else {
            neighbour += LEFT;
        }
    }
    if (gd->map[r + 1][c] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r + 1][c] != GHOST_ONLY) {
                neighbour += RIGHT;
            }
        } else {
            neighbour += RIGHT;
        }
    }
    if (gd->map[r][c - 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r][c - 1] != GHOST_ONLY) {
                neighbour += UP;
            }
        } else {
            neighbour += UP;
        }
    }
    if (gd->map[r][c + 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r][c + 1] != GHOST_ONLY) {
                neighbour += DOWN;
            }
        } else {
            neighbour += DOWN;
        }
    }

    ghost->calculateTarget(gd->pacman->getX(), gd->pacman->getY(), this->chase);
    Direction direction = ghost->calculatePath(neighbour);
    if (direction == 0) {
        //std::cout << "neighbour " << neighbour << "\n";
        return;
    }

    if ((direction == LEFT && ghost->getDirection() == RIGHT) ||
        (direction == RIGHT && ghost->getDirection() == LEFT) ||
        (direction == UP && ghost->getDirection() == DOWN) ||
        (direction == DOWN && ghost->getDirection() == UP)) {
        return;
    }

    bool directionChanged = false;
    if (ghost->getDirection() != direction) directionChanged = true;

    if (directionChanged) {
        ghost->setDirection(direction);
        ghost->norm();
        ghost->setCooldown(0.0);
    }
}

bool Game::checkIfCanMoveGhost(Ghost *ghost) {
    float x = ghost->getX();
    float y = ghost->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);

    if (r == 0 || r == -1 || r == 28 || r == 29) return true;

    if (ghost->getDirection() == LEFT && gd->map[r - 1][c] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r - 1][c] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == RIGHT && gd->map[r + 1][c] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r + 1][c] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == UP && gd->map[r][c - 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r][c - 1] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    } else if (ghost->getDirection() == DOWN && gd->map[r][c + 1] != WALL) {
        if (ghost->getIsOutside()) {
            if (gd->map[r][c + 1] != GHOST_ONLY) {
                return true;
            }
            return false;
        }
        return true;
    }

    return false;
}

void Game::moveGhost(Ghost *ghost) {
    if (!checkIfCanMoveGhost(ghost)) return;
    if (ghost->getX() <= 0.3) ghost->setX(27.7);
    else if (ghost->getX() >= 27.7) ghost->setX(0.3);

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
    float x = ghost->getX();
    float y = ghost->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);

    if (gd->map[r][c] != GHOST_ONLY) {
        ghost->setIsOutside(true);
    } else {
        ghost->setIsOutside(false);
    }
}

bool Game::checkIfWon() {
    return gd->numberOfDots == 0;
}

bool Game::checkIfDead() {
    for (auto &ghost: gd->ghosts) {
        if (Entity::checkCollision(gd->pacman, ghost)) return true;
    }
    return false;
}

void Game::enableNext() {
    if (gd->enabled == GameData::NUMBER_OF_GHOSTS) return;

    gd->ghosts[gd->enabled]->setEnabled(true);
    gd->enabled++;
}
