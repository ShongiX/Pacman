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
    //pacman
    move(gd->pacman);
    eat();

    //ghosts
    for (int i=0; i<4; ++i) {
        if (i==0) {
            //std::cout << gd->ghosts[i]->getX() << " " << gd->ghosts[i]->getY() << "\n";
            std::cout << gd->ghosts[0]->getDirection() << "\n";
        }

        setIfOutside(gd->ghosts[i]);
        turnGhost(gd->ghosts[i]);
        moveGhost(gd->ghosts[i]);
    }

    //game state
    if (checkIfWon()) gd->gameWon = true;
    if (checkIfDead()) {
        gd->gameOver = true;
    }
}

void Game::flip() {
    chase = !chase;
    for (auto & ghost : gd->ghosts) {
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
    if ((direction == LEFT && gd->pacman->getDirection() == RIGHT) ||
        (direction == RIGHT && gd->pacman->getDirection() == LEFT) ||
        (direction == UP && gd->pacman->getDirection() == DOWN) ||
        (direction == DOWN && gd->pacman->getDirection() == UP)) {
        return false;
    }

    float x = gd->pacman->getX();
    float y = gd->pacman->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);
    if (direction == LEFT) {
        if (gd->map[r][c] != WALL && gd->map[r - 1][c] != WALL) {
            return true;
        }
    } else if (direction == RIGHT) {
        if (gd->map[r][c] != WALL && gd->map[r + 1][c] != WALL) {
            return true;
        }
    } else if (direction == UP) {
        if (gd->map[r][c] != WALL && gd->map[r][c - 1] != WALL) {
            return true;
        }
    } else if (direction == DOWN) {
        if (gd->map[r][c] != WALL && gd->map[r][c + 1] != WALL) {
            return true;
        }
    }

    return false;
}

void Game::turn(Direction direction) {
    gd->pacman->setDirection(direction);
    gd->pacman->norm();
}

bool Game::checkIfCanMove(DynamicEntity *entity) {
    if (entity->getDirection() == LEFT &&
        gd->map[(int) std::round(entity->getX() - 0.5)][(int) std::round(entity->getY())] != WALL) {
        return true;
    } else if (entity->getDirection() == RIGHT &&
               gd->map[(int) std::round(entity->getX() + 0.5)][(int) std::round(entity->getY())] != WALL) {
        return true;
    } else if (entity->getDirection() == UP &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() - 0.5)] != WALL) {
        return true;
    } else if (entity->getDirection() == DOWN &&
               gd->map[(int) std::round(entity->getX())][(int) std::round(entity->getY() + 0.5)] != WALL) {
        return true;
    }

    return false;
}

void Game::move(DynamicEntity *entity) {
    if (!checkIfCanMove(entity)) return;

    if (entity->getDirection() == LEFT) {
        entity->move(-MOVE_STEP, 0);
        if (entity->getX() < -0.5) entity->setX(28);
    } else if (entity->getDirection() == RIGHT) {
        entity->move(MOVE_STEP, 0);
        if (entity->getX() > 28.5) entity->setX(0);
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

    /*if (ghost->getDirection() == LEFT) {
        r = std::floor(x);
        c = std::round(y);
    } else if (ghost->getDirection() == RIGHT) {
        r = std::ceil(x);
        c = std::round(y);
    } else if (ghost->getDirection() == UP) {
        r = std::round(x);
        c = std::floor(y);
    } else if (ghost->getDirection() == DOWN) {
        r = std::round(x);
        c = std::ceil(y);
    }*/

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

    ghost->calculateTarget(gd->pacman->getX(), gd->pacman->getY(),this->chase);
    Direction direction = ghost->calculatePath(neighbour);

    if ((direction == LEFT && ghost->getDirection() == RIGHT) ||
        (direction == RIGHT && ghost->getDirection() == LEFT) ||
        (direction == UP && ghost->getDirection() == DOWN) ||
        (direction == DOWN && ghost->getDirection() == UP)) {
        return;
    }

    bool directionChanged = false;
    if (ghost->getDirection() != direction) directionChanged = true;

    ghost->setDirection(direction);
    if (directionChanged) {
        ghost->norm();
        ghost->setCooldown(0.0);
    }
}

bool Game::checkIfCanMoveGhost(Ghost *ghost) {
    float x = ghost->getX();
    float y = ghost->getY();
    int r = (int) std::round(x);
    int c = (int) std::round(y);

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

    if (ghost->getDirection() == LEFT) {
        ghost->move(-MOVE_STEP, 0);
        if (ghost->getX() < -0.5) ghost->setX(28);
    } else if (ghost->getDirection() == RIGHT) {
        ghost->move(MOVE_STEP, 0);
        if (ghost->getX() > 28.5) ghost->setX(0);
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
    for (auto & ghost : gd->ghosts) {
        if (Entity::checkCollision(gd->pacman, ghost)) return true;
    }
    return false;
}
