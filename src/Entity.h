#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "EntityState.h"

class Level;

class Entity
{
protected:
    int hitPoints;
    int maxHitPoints;
    int armor;
    float speed;
    int attack;
    float attackSpeed;
    int attackRange;
    float projectileSpeed;
    bool isInvincible = false;
    sf::Vector2f position;
    sf::Vector2f previousPosition;
    std::unique_ptr<EntityState> state;
    Level *level;
    float lastAttackTime = 0.f;

public:
    // Getters
    int getHitPoints() const;
    int getMaxHitPoints() const;
    int getArmor() const;
    float getSpeed() const;
    int getAttack() const;
    float getAttackSpeed() const;
    int getAttackRange() const;
    float getProjectileSpeed() const;
    bool getInvincible() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getPreviousPosition() const;
    sf::Sprite getSprite();
    EntityState *getState() const;
    Level *getLevel() const;
    float getLastAttackTime() const;
    // Setters
    void setHitPoints(int hp);
    void setMaxHitPoints(int hp);
    void setArmor(int a);
    void setSpeed(float s);
    void setAttack(int a);
    void setAttackSpeed(float as);
    void setAttackRange(int ar);
    void setProjectileSpeed(float ps);
    void setInvincible(bool i);
    void setPosition(const sf::Vector2f &p);
    void setPreviousPosition(const sf::Vector2f &p);
    void setSprite(const sf::Sprite &s);
    void setState(std::unique_ptr<EntityState> s);
    void setLevel(Level *l);
    void setLastAttackTime(float &t);
    // Methods
    void addImg(const std::string &imagePath);
    void setGlobalPosition(const sf::Vector2f &p);
    void setSpriteRotation(float angle);
    void setOrientation(bool facingRight);
    void render(float deltaTime, sf::RenderWindow *w);
    void newState(std::unique_ptr<EntityState> e);
    void move(sf::Vector2f direction, float deltaTime);
    void attackEntity(Entity *entity);
    void defendAgainstEntity(Entity *entity);
    bool isInRange(Entity *entity);
    bool isAlive() const;
    void startInvincibility();
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(sf::Event &event) = 0;
    virtual void stateIdle() = 0;
    virtual void stateMove() = 0;
    virtual void stateDie() = 0;
    virtual void stateHit() = 0;
    virtual void stateAttack() = 0;
    virtual ~Entity() {};
};

#endif // ENTITY_H
