#ifndef PROJECTILE_TNT_H
#define PROJECTILE_TNT_H

#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ProjectileTNT : public Projectile
{
private:
public:
    // Constructor
    ProjectileTNT(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const float speed, const int damages, int penetration);
    // Getters
    // Setters
    // Methods
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
};

#endif // PROJECTILE_TNT_H