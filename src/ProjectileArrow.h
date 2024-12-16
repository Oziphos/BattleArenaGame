#ifndef PROJECTILE_ARROW_H
#define PROJECTILE_ARROW_H

#include <SFML/Graphics.hpp>
#include "Projectile.h"

class ProjectileArrow : public Projectile
{
private:
public:
    // Constructor
    ProjectileArrow(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const float speed, const int damages, int penetration);
    // Getters
    // Setters
    // Methods
    void stateIdle() override;
    void stateMove() override;
    void stateDie() override;
    void stateHit() override;
    void stateAttack() override;
};

#endif // PROJECTILE_ARROW_H