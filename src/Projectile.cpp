#include "Projectile.h"
#include "Entity.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"
#include "Level.h"
#include <cmath>
#include <iostream>

// Getters
sf::Vector2f Projectile::getDirection() const
{
    return direction;
}

int Projectile::getPenetration() const
{
    return penetration;
}

float Projectile::getAngle() const
{
    return angle;
}
// Setters
void Projectile::setDirection(const sf::Vector2f &d)
{
    direction = d;
}

void Projectile::setPenetration(int p)
{
    penetration = p;
}

void Projectile::setAngle(float a)
{
    angle = a;
}

// Methods
void Projectile::update(float deltaTime)
{
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0.f)
    {
        direction /= magnitude;
    }
    this->move(direction, deltaTime);
}

void Projectile::handleEvent(sf::Event &e)
{
}

void Projectile::stateIdle()
{
    this->newState(std::make_unique<EntityStateIdle>("arrow"));
    this->setGlobalPosition(this->getPosition());
}

void Projectile::stateMove()
{
    this->newState(std::make_unique<EntityStateMove>("arrow"));
    this->setGlobalPosition(this->getPosition());
}

void Projectile::stateDie()
{
}

void Projectile::stateHit()
{
}

void Projectile::stateAttack()
{
}

bool Projectile::isOutOfBounds() const
{
    const sf::RenderWindow *window = level->getWindow();
    sf::Vector2u windowSize = window->getSize();

    sf::Vector2f position = this->getPosition();
    return (
        position.x < 0 ||
        position.x > static_cast<float>(windowSize.x) ||
        position.y < 0 ||
        position.y > static_cast<float>(windowSize.y));
}

void Projectile::markForRemoval()
{
    markedForRemoval = true;
}

bool Projectile::isMarkedForRemoval() const
{
    return markedForRemoval;
}