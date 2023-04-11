//
// Created by laccs on 4/8/2023.
//

#ifndef PACMAN_ENTITY_HPP
#define PACMAN_ENTITY_HPP

/**
 * This is a class, for representing an entity on the game map
 */
class Entity {
protected:
    // The position of the entity in the map coordinates
    float x, y;

    // The collision treshold of the entity
    static float COLLISION_TRESHOLD;

public:
    static bool checkCollision(Entity *a, Entity *b);

    float getX() const;

    void setX(float _x);

    float getY() const;
};


#endif //PACMAN_ENTITY_HPP
