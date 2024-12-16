#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Wave;

class Player : public Entity
{
private:
public:
    // Constructor
    Player();
    // Getters
    // Setters
    // Methods
    void handleEvent(sf::Event &e) override;
    void update(float deltaTime) override;
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
    void handleContinuousInput(float deltaTime);
    Entity *getNearestEnnemy(Wave *wave) const;
};

#endif // PLAYER_H