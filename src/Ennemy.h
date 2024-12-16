#ifndef ENNEMY_H
#define ENNEMY_H

#include "Entity.h"

class Player;

class Ennemy : public Entity
{
private:
    Player *player;

public:
    // Getters
    Player *
    getPlayer();
    // Setters
    void setPlayer(Player *p);
    // Virtual methods
    void moveToAttackRange(float deltaTime);
    void attackPlayer();
    // Override methods
    void update(float deltaTime) override;
    void handleEvent(sf::Event &e) override;
    virtual void stateIdle() override = 0;
    virtual void stateMove() override = 0;
    virtual void stateDie() override = 0;
    virtual void stateHit() override = 0;
    virtual void stateAttack() override = 0;
    sf::Vector2f getPlayerDirection() const;
};

#endif // ENNEMY_H