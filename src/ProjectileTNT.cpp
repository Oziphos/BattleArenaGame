#include "ProjectileTNT.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"
#include "EntityStateDead.h"
#include "EntityStateHit.h"
#include <thread>
#include <chrono>
#include <cmath>

// Constructor
ProjectileTNT::ProjectileTNT(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const float speed, const int damages, int penetration)
{
    this->setLevel(l);
    this->setHitPoints(1);
    this->setMaxHitPoints(1);
    this->setArmor(0);
    this->setSpeed(speed);
    this->setDirection(direction);
    this->setPenetration(penetration);
    this->setAttack(damages);
    this->setAttackSpeed(0.0f);
    this->setAttackRange(0);
    this->setProjectileSpeed(0.f);
    this->setState(std::make_unique<EntityStateMove>("tnt"));
    this->setGlobalPosition(position);
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
    this->setAngle(angle);
    this->setSpriteRotation(angle);
}
// Getters

// Setters

// Methods
void ProjectileTNT::stateIdle()
{
    this->newState(std::make_unique<EntityStateIdle>("tnt"));
    this->setGlobalPosition(this->getPosition());
}

void ProjectileTNT::stateMove()
{
    this->newState(std::make_unique<EntityStateMove>("tnt"));
    this->setGlobalPosition(this->getPosition());
}

void ProjectileTNT::stateDie()
{
}

void ProjectileTNT::stateHit()
{
}

void ProjectileTNT::stateAttack()
{
    this->newState(std::make_unique<EntityStateMove>("tnt"));
    this->setGlobalPosition(this->getPosition());
}