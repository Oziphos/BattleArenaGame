#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityState.h"
#include "Ennemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Obstacle.h"
#include "Level.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

// Getters
int Entity::getHitPoints() const { return hitPoints; }

int Entity::getMaxHitPoints() const { return maxHitPoints; }

int Entity::getArmor() const { return armor; }

float Entity::getSpeed() const { return speed; }

int Entity::getAttack() const { return attack; }

float Entity::getAttackSpeed() const { return attackSpeed; }

int Entity::getAttackRange() const { return attackRange; }

float Entity::getProjectileSpeed() const { return projectileSpeed; }

sf::Vector2f Entity::getPosition() const { return position; }

bool Entity::getInvincible() const { return isInvincible; }

sf::Vector2f Entity::getPreviousPosition() const { return previousPosition; }

sf::Sprite Entity::getSprite() { return state->getSprite(); }

EntityState *Entity::getState() const { return state.get(); }

Level *Entity::getLevel() const { return level; }

float Entity::getLastAttackTime() const { return lastAttackTime; }

// Setters
void Entity::setHitPoints(int hp) { hitPoints = hp; }

void Entity::setMaxHitPoints(int hp) { maxHitPoints = hp; }

void Entity::setArmor(int a) { armor = a; }

void Entity::setSpeed(float s) { speed = s; }

void Entity::setAttack(int a) { attack = a; }

void Entity::setAttackSpeed(float as) { attackSpeed = as; }

void Entity::setAttackRange(int ar) { attackRange = ar; }

void Entity::setProjectileSpeed(float ps) { projectileSpeed = ps; }

void Entity::setInvincible(bool i) { isInvincible = i; }

void Entity::setPosition(const sf::Vector2f &p) { position = p; }

void Entity::setPreviousPosition(const sf::Vector2f &p) { previousPosition = p; }

void Entity::setSprite(const sf::Sprite &s) { state->setSprite(s); }

void Entity::setState(std::unique_ptr<EntityState> s)
{
    state = std::move(s);
}

void Entity::setLevel(Level *l)
{
    level = l;
}

void Entity::setLastAttackTime(float &t)
{
    lastAttackTime = t;
}
// Methods
void Entity::setGlobalPosition(const sf::Vector2f &p)
{
    previousPosition = position;
    this->setPosition(p);
    state->setGlobalPosition(p);
}

void Entity::setSpriteRotation(float angle)
{
    state->setRotation(angle);
}

void Entity::setOrientation(bool facingRight)
{
    state->setOrientation(facingRight);
}

void Entity::render(float deltaTime, sf::RenderWindow *window)
{
    if (Projectile *projectile = dynamic_cast<Projectile *>(this))
    {
        this->setSpriteRotation(projectile->getAngle());
    }
    state->render(deltaTime, window);
}

void Entity::newState(std::unique_ptr<EntityState> newState)
{
    newState->copyFrom(*this->getState());
    this->setState(std::move(newState));
}

void Entity::move(sf::Vector2f direction, float deltaTime)
{

    if (direction != sf::Vector2f(0.f, 0.f))
    {
        float entitySpeed = this->getSpeed();
        sf::Vector2f movement = direction * entitySpeed * deltaTime;

        sf::Vector2f newPosition = this->getPosition() + movement;
        this->setGlobalPosition(newPosition);
        if (direction.x > 0)
        {
            this->setOrientation(true);
        }
        else if (direction.x < 0)
        {
            this->setOrientation(false);
        }
        this->stateMove();
    }
    else
    {
        this->stateIdle();
    }
}

void Entity::attackEntity(Entity *e)
{
    if (attackRange <= 50)
    {
        // Melee units
        e->defendAgainstEntity(this);
    }
    else
    {

        sf::Vector2f direction = e->getPosition() - this->getPosition();
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (magnitude != 0.f)
        {
            direction /= magnitude; // Normalisation
        }
        if (e == level->getGameManager()->getPlayer())
        {
            auto projectile = std::make_unique<ProjectileTNT>(
                level,
                this->getPosition(),        // Start position of the projectile
                direction,                  // Target direction
                this->getProjectileSpeed(), // Speed of the projectile
                this->getAttack(),          // Damage of the projectile
                1                           // Penetration value
            );
            level->addEnnemyProjectile(std::move(projectile));
        }
        else
        {
            auto projectile = std::make_unique<ProjectileArrow>(
                level,
                this->getPosition(),        // Start position of the projectile
                direction,                  // Target direction
                this->getProjectileSpeed(), // Speed of the projectile
                this->getAttack(),          // Damage of the projectile
                1                           // Penetration value
            );
            level->addPlayerProjectile(std::move(projectile));
        }
    }
}

void Entity::defendAgainstEntity(Entity *e)
{
    int attackValue = e->getAttack();
    int damage = attackValue - armor;
    if (damage > 0)
    {
        this->stateHit();
        this->hitPoints -= damage;
    }

    if (this->hitPoints <= 0)
    {
        this->hitPoints = 0;
    }
    else
    {
        this->startInvincibility();
    }
}

bool Entity::isInRange(Entity *e)
{
    sf::Vector2f myPos = this->getPosition();
    sf::Vector2f entityPos = e->getPosition();

    float distance = std::sqrt(std::pow(myPos.x - entityPos.x, 2) + std::pow(myPos.y - entityPos.y, 2));

    return (distance <= (this->getAttackRange()));
}

bool Entity::isAlive() const
{
    return hitPoints > 0;
}

void Entity::startInvincibility()
{
    this->setInvincible(true);
    // Exemple avec une librairie de gestion de temps
    std::thread([this]()
                {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Durée d'invincibilité
        this->setInvincible(false); })
        .detach();
}
