#include "Player.h"
#include "Wave.h"
#include "Entity.h"
#include "EntityStateMove.h"
#include "EntityStateIdle.h"
#include "EntityStateHit.h"
#include "EntityStateDead.h"
#include "Ennemy.h"
#include "Level.h"
#include <cmath>
#include <memory>
#include <vector>

// Constructors
Player::Player()
{
    this->setHitPoints(200);
    this->setMaxHitPoints(200);
    this->setArmor(10);
    this->setSpeed(150);
    this->setAttack(20);
    this->setAttackSpeed(2.0f);
    this->setAttackRange(400);
    this->setProjectileSpeed(180);
    this->setState(std::make_unique<EntityStateIdle>("player"));
    this->setGlobalPosition(sf::Vector2f(20, 20));
}

// Getters
// Setters
// Methods
void Player::update(float deltaTime)
{
    Entity *e = this->getNearestEnnemy(level->getActualWave());
    if (e)
    {
        if (this->isInRange(e))
        {
            lastAttackTime += deltaTime;
            if (lastAttackTime >= (1.f / this->getAttackSpeed()))
            {
                this->attackEntity(e);
                lastAttackTime = 0.f;
            }
        }
    }

    this->handleContinuousInput(deltaTime);
}

void Player::handleEvent(sf::Event &e)
{
}

void Player::stateIdle()
{
    this->newState(std::make_unique<EntityStateIdle>("player"));
    this->setGlobalPosition(this->getPosition());
}

void Player::stateMove()
{
    this->newState(std::make_unique<EntityStateMove>("player"));
    this->setGlobalPosition(this->getPosition());
}

void Player::stateDie()
{
    this->newState(std::make_unique<EntityStateDead>("player"));
    this->setGlobalPosition(this->getPosition());
}

void Player::stateHit()
{
    this->newState(std::make_unique<EntityStateHit>("player"));
    this->setGlobalPosition(this->getPosition());
}

void Player::stateAttack()
{
}

void Player::handleContinuousInput(float deltaTime)
{
    sf::Vector2f actualPosition = this->getPosition();
    sf::Vector2f direction(0.f, 0.f); // Initialisation de la direction

    float playerSpeed = this->getSpeed() * deltaTime;

    // Vérification des touches pressées pour définir la direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) // Haut
    {
        direction.y -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // Gauche
    {
        direction.x -= playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Bas
    {
        direction.y += playerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Droite
    {
        direction.x += playerSpeed;
    }

    // Récupérer la fenêtre et ses dimensions
    sf::RenderWindow *window = this->getLevel()->getWindow();
    sf::Vector2u windowSize = window->getSize();

    // Calcul de la nouvelle position
    sf::Vector2f newPosition = actualPosition + direction;

    // Vérifier si la nouvelle position est en dehors des limites
    const float minX = 0.f;
    const float minY = 0.f;
    const float maxX = static_cast<float>(windowSize.x);
    const float maxY = static_cast<float>(windowSize.y);

    if (newPosition.x < minX || newPosition.x > maxX || 
        newPosition.y < minY || newPosition.y > maxY)
    {
        // Si en dehors des limites, annuler le mouvement
        direction = sf::Vector2f(0.f, 0.f);
    }

    // Appliquer la direction à la fonction move
    this->move(direction, deltaTime);
}


Entity *Player::getNearestEnnemy(Wave *wave) const
{
    Entity *nearestEnnemy = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (const auto &ennemyPtr : wave->getRenderableEnnemies())
    {

        if (!ennemyPtr->isAlive())
        {
            continue;
        }
        sf::Vector2f ennemyPosition = ennemyPtr->getPosition();
        sf::Vector2f playerPosition = this->getPosition();

        float distance = std::sqrt((ennemyPosition.x - playerPosition.x) * (ennemyPosition.x - playerPosition.x) +
                                   (ennemyPosition.y - playerPosition.y) * (ennemyPosition.y - playerPosition.y));

        if (distance < minDistance)
        {
            minDistance = distance;
            nearestEnnemy = ennemyPtr.get();
        }
    }

    return nearestEnnemy;
}
