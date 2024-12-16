#include "EnnemyMarksman.h"
#include "EntityStateIdle.h"
#include "EntityStateMove.h"
#include "EntityStateDead.h"
#include "EntityStateHit.h"
#include <thread>
#include <chrono>

// Constructor
EnnemyMarksman::EnnemyMarksman(Level *level, Player *p, int lvlId, int waveNb)
{
    this->setLevel(level);
    this->setPlayer(p);
    this->setHitPoints(40 + (2 * lvlId * waveNb));
    this->setMaxHitPoints(40 + (2 * lvlId * waveNb));
    this->setArmor(0);
    this->setSpeed(90);
    this->setAttack(30 + waveNb);
    this->setAttackSpeed(0.6f);
    this->setAttackRange(600);
    this->setProjectileSpeed(120);
    this->setState(std::make_unique<EntityStateMove>("marksman"));
    this->setGlobalPosition(sf::Vector2f(20, 20));
}

// Getters

// Setters

// Methods
void EnnemyMarksman::stateIdle()
{
    this->newState(std::make_unique<EntityStateIdle>("marksman"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemyMarksman::stateMove()
{
    this->newState(std::make_unique<EntityStateMove>("marksman"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemyMarksman::stateDie()
{
    this->newState(std::make_unique<EntityStateDead>("marksman"));
    this->setGlobalPosition(this->getPosition());
}

void EnnemyMarksman::stateHit()
{
    this->newState(std::make_unique<EntityStateMove>("marksman"));
    this->setGlobalPosition(this->getPosition());
    std::thread([this]()
                { 
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    this->newState(std::make_unique<EntityStateMove>("marksman"));this->setGlobalPosition(this->getPosition()); })
        .detach();
}

void EnnemyMarksman::stateAttack()
{
    this->newState(std::make_unique<EntityStateIdle>("marksman"));
    this->setGlobalPosition(this->getPosition());
}