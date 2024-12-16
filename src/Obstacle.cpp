#include "Obstacle.h"
#include "EntityStateIdle.h"
// Constructor
Obstacle::Obstacle(Level *level, const sf::Vector2f position, const bool isCollisionable, const bool isDestroyable) : collisionable(isCollisionable), destroyable(isDestroyable)
{
    this->setLevel(level);
    this->setHitPoints(50);
    this->setMaxHitPoints(50);
    this->setArmor(0);
    this->setSpeed(0);
    this->setAttack(0);
    this->setAttackSpeed(0.f);
    this->setAttackRange(0);
    this->setProjectileSpeed(0.f);
    this->setState(std::make_unique<EntityStateIdle>("bush"));
    this->setGlobalPosition(position);
}

// Getters
bool Obstacle::getCollisionable() const
{
    return collisionable;
}

bool Obstacle::getDestroyable() const { return destroyable; }

// Setters
void Obstacle::setCollisionable(const bool b)
{
    collisionable = b;
}

void Obstacle::setDestroyable(const bool b)
{
    destroyable = b;
}

// Methods
void Obstacle::update(float deltaTime)
{
}

void Obstacle::handleEvent(sf::Event &e)
{
}

void Obstacle::stateIdle()
{
}

void Obstacle::stateMove()
{
}

void Obstacle::stateDie()
{
}

void Obstacle::stateHit()
{
}

void Obstacle::stateAttack()
{
}
