#include "EnnemySoldier.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"
#include "EntityStateDead.h"
#include "EntityStateHit.h"
#include "EntityStateAttack.h"
#include <thread>
#include <chrono>

// Constructor
EnnemySoldier::EnnemySoldier(Level *level, Player *p, int lvlId, int waveNb)
{
    this->setLevel(level);
    this->setPlayer(p);
    this->setHitPoints(60 + (2 * lvlId * waveNb));
    this->setMaxHitPoints(60 + (2 * lvlId * waveNb));
    this->setArmor(0);
    this->setSpeed(90 + (2 * waveNb));
    this->setAttack(15 + waveNb);
    this->setAttackSpeed(1.0f);
    this->setAttackRange(50);
    this->setProjectileSpeed(140);
    this->setState(std::make_unique<EntityStateMove>("soldier"));
    this->setGlobalPosition(sf::Vector2f(20, 20));
}

// Getters

// Setters

// Methods
void EnnemySoldier::stateIdle()
{
    this->newState(std::make_unique<EntityStateIdle>("soldier"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemySoldier::stateMove()
{
    this->newState(std::make_unique<EntityStateMove>("soldier"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemySoldier::stateDie()
{
    this->newState(std::make_unique<EntityStateDead>("soldier"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemySoldier::stateHit()
{
    this->newState(std::make_unique<EntityStateHit>("soldier"));
    this->setGlobalPosition(this->getPosition());
    std::thread([this]()
                { 
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    this->newState(std::make_unique<EntityStateMove>("soldier"));this->setGlobalPosition(this->getPosition()); })
        .detach();
}

void EnnemySoldier::stateAttack()
{
    this->newState(std::make_unique<EntityStateAttack>("soldier"));
    this->setGlobalPosition(this->getPosition());
}