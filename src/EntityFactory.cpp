#include "EntityFactory.h"

std::unique_ptr<Player> EntityFactory::createPlayer()
{
    return std::make_unique<Player>();
}

std::unique_ptr<EnnemySoldier> EntityFactory::createEnnemySoldier(Level *l, Player *p, int lvlId, int waveNb)
{
    return std::make_unique<EnnemySoldier>(l, p, lvlId, waveNb);
}

std::unique_ptr<EnnemyMarksman> EntityFactory::createEnnemyMarksman(Level *l, Player *p, int lvlId, int waveNb)
{
    return std::make_unique<EnnemyMarksman>(l, p, lvlId, waveNb);
}

std::unique_ptr<Obstacle> EntityFactory::createObstacle(Level *l, const sf::Vector2f position, bool isCollisionable, bool isDestroyable)
{
    return std::make_unique<Obstacle>(l, position, isCollisionable, isDestroyable);
}

std::unique_ptr<Projectile> EntityFactory::createProjectileArrow(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const int speed, const int damages, int penetration)
{
    return std::make_unique<ProjectileArrow>(l, position, direction, speed, damages, penetration);
}

std::unique_ptr<Projectile> EntityFactory::createProjectileTNT(Level *l, const sf::Vector2f position, const sf::Vector2f direction, const int speed, const int damages, int penetration)
{
    return std::make_unique<ProjectileTNT>(l, position, direction, speed, damages, penetration);
}

std::vector<std::unique_ptr<Entity>> EntityFactory::createWave(int lvlId, int waveNb)
{
    // TODO
}