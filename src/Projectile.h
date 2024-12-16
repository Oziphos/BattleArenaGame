#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Entity;

class Projectile : public Entity
{
private:
    sf::Vector2f direction;
    sf::Vector2f destination;
    int penetration;
    float angle;
    bool markedForRemoval = false;

public:
    // Getters
    sf::Vector2f getDirection() const;
    int getPenetration() const;
    float getAngle() const;
    // Setters
    void setDirection(const sf::Vector2f &d);
    void setPenetration(int p);
    void setAngle(float a);
    // Methods
    void update(float deltaTime) override;
    void handleEvent(sf::Event &e) override;
    bool isOutOfBounds() const;
    void markForRemoval();
    bool isMarkedForRemoval() const;
    virtual void stateIdle() override = 0;
    virtual void stateMove() override = 0;
    virtual void stateDie() override = 0;
    virtual void stateHit() override = 0;
    virtual void stateAttack() override = 0;
};

#endif // OBSTACLE_H
