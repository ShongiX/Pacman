//
// Created by laccs on 4/8/2023.
//

#ifndef PACMAN_ENTITY_HPP
#define PACMAN_ENTITY_HPP

class Entity {
protected:
    float x,y; //map coordinates

    static float COLLISION_TRESHOLD;

public:
    static bool checkCollision(Entity* a, Entity* b);

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
};


#endif //PACMAN_ENTITY_HPP
