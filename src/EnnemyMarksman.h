#ifndef ENNEMY_MARKSMAN_H
#define ENNEMY_MARKSMAN_H

#include <SFML/Graphics.hpp>
#include "Ennemy.h"
#include "Player.h"

class Ennemy;
class Player;

class EnnemyMarksman : public Ennemy
{
private:
public:
    // Constructor
    EnnemyMarksman(Level *level, Player *p, int lvlId, int waveNb);
    // Getters
    // Setters
    // Methods
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
};

#endif // ENNEMY_MARKSMAN_H