#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Entity.h"
#include "Player.h"

class Level;
class Entity;
class Player;

class CollisionHandler
{
private:
    Player *player;
    sf::RenderWindow *window;

public:
    // Constructors
    CollisionHandler(sf::RenderWindow *w, Player *p);
    // Getters
    Player *getPlayer() const;
    sf::RenderWindow *getWindow() const;
    // Setters
    void setPlayer(Player *p);
    void setWindow(sf::RenderWindow *w);
    // Methods
    void setSpawnPosition(Level *lvl, Entity *e);
    bool isPositionFree(const sf::Vector2f &position, Level *lvl) const;
    sf::Vector2f generateRandomPosition(float maxX, float maxY);
    bool isPositionInAttackRange(const sf::Vector2f &candidatePosition, const sf::Vector2f &playerPosition, float attackRange);
    bool checkCollision(Entity *a, Entity *b);
    void resolveCollision(Entity *a, Entity *b);
};

#endif // COLLISION_HANDLER_H
