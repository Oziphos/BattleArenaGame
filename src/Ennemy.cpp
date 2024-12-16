#include "Ennemy.h"
#include "EnnemySoldier.h"
#include "EntityStateMove.h"
#include "EntityStateIdle.h"
#include "EntityStateDead.h"
#include "Player.h"
#include "Level.h"
#include <math.h>

// Getters
Player *Ennemy::getPlayer() { return player; }

// Setters
void Ennemy::setPlayer(Player *p) { player = p; }

// Methods
void Ennemy::moveToAttackRange(float deltaTime)
{
    sf::Vector2f direction = this->getPlayerDirection();
    this->move(direction, deltaTime);
}

void Ennemy::attackPlayer()
{
    Player *p = this->getPlayer();
    this->attackEntity(p);
}

void Ennemy::update(float deltaTime)
{
    if (this->isAlive())
    {

        if (this->isInRange(this->getPlayer()))
        {
            this->stateAttack();
            lastAttackTime += deltaTime;
            if (lastAttackTime >= (1.f / this->getAttackSpeed()))
            {
                this->attackPlayer();
                lastAttackTime = 0.f;
            }
        }
        else
        {
            this->moveToAttackRange(deltaTime);
        }
    }
    else
    {

        this->stateDie();
    }
}

void Ennemy::handleEvent(sf::Event &e)
{
    // TODO: Implement handleEvent behavior
}

sf::Vector2f Ennemy::getPlayerDirection() const
{
    sf::Vector2f ennemyPos = this->getPosition();
    sf::Vector2f playerPos = player->getPosition();

    // Calculer la distance entre l'ennemi et le joueur
    float distance = std::sqrt(std::pow(ennemyPos.x - playerPos.x, 2) + std::pow(ennemyPos.y - playerPos.y, 2));

    sf::Vector2f direction = playerPos - ennemyPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction /= length;
    }

    return direction;
}
