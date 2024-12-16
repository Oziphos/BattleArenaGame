#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Player.h"
#include "Ennemy.h"
#include "EnnemySoldier.h"
#include "EnnemyMarksman.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include "Obstacle.h"
#include "Projectile.h"
#include "ProjectileArrow.h"
#include "ProjectileTNT.h"

class EntityFactory
{
private:
public:
    std::unique_ptr<Player> createPlayer();
    std::unique_ptr<EnnemySoldier> createEnnemySoldier(Level *l, Player *p, int lvlId, int waveNb);
    std::unique_ptr<EnnemyMarksman> createEnnemyMarksman(Level *l, Player *p, int lvlId, int waveNb);
    std::unique_ptr<Obstacle> createObstacle(Level *l, const sf::Vector2f position, bool isCollisionable, bool isDestroyable);
    std::unique_ptr<Projectile> createProjectileArrow(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const int speed, const int damages, int penetration);
    std::unique_ptr<Projectile> createProjectileTNT(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const int speed, const int damages, int penetration);
    std::vector<std::unique_ptr<Entity>> createWave(int lvlId, int waveNb);
    // Ennemy createEnnemyScout();
    // Ennemy createEnnemyTank();
    // Obstacle createObstacleWall(int width, int height);
    // Projectile createProjectile(Entity * source, Entity * destination);
};

#endif // ENTITY_FACTORY_H
