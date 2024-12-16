#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Obstacle : public Entity
{
private:
    bool collisionable;
    bool destroyable;

public:
    // Constructors
    Obstacle(Level *level, const sf::Vector2f position, const bool isCollisionable, const bool isDestroyable);
    // Getters
    bool getCollisionable() const;
    bool getDestroyable() const;
    // Setters
    void setCollisionable(const bool b);
    void setDestroyable(const bool b);
    // Methods
    void update(float deltaTime) override;
    void handleEvent(sf::Event &e) override;
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
};

#endif // OBSTACLE_H
