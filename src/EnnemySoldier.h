#ifndef ENNEMY_SOLDIER_H
#define ENNEMY_SOLDIER_H

#include <SFML/Graphics.hpp>
#include "Ennemy.h"
#include "Player.h"

class Ennemy;
class Player;

class EnnemySoldier : public Ennemy
{
private:
public:
    // Constructor
    EnnemySoldier(Level *level, Player *p, int lvlId, int waveNb);
    // Getters
    // Setters
    // Methods
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
};

#endif // ENNEMY_SOLDIER_H