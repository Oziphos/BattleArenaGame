#ifndef WAVE_H
#define WAVE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Player;
class Ennemy;
class EntityFactory;
class CollisionHandler;
class Level;

class Wave
{
private:
    std::vector<std::unique_ptr<Ennemy>> renderableEnnnemies;
    std::vector<std::unique_ptr<Ennemy>> ennemies;
    EntityFactory *factory;
    CollisionHandler *collisionHandler;
    Level *lvl;

    float spawnTimer = 0.0f;
    const float spawnInterval = 0.8f;
    int calculateBaseEnemyCount(int lvlId, int waveNb) const;

public:
    // Constructor
    Wave(Level *lvl, int lvlId, int waveNb, Player *p);
    // Getters
    const std::vector<std::unique_ptr<Ennemy>> &
    getEnnemies() const;
    const std::vector<std::unique_ptr<Ennemy>> &
    getRenderableEnnemies() const;
    EntityFactory *getFactory() const;
    CollisionHandler *getCollisionHandler() const;
    float getSpawnTimer() const;
    float getSpawnInterval() const;
    Level *getLevel() const;
    // Setters
    void setEnnemies(std::vector<std::unique_ptr<Ennemy>> &&e);
    void setRenderableEnnemies(std::vector<std::unique_ptr<Ennemy>> &&e);
    void setFactory(EntityFactory *f);
    void setCollisionHandler(CollisionHandler *ch);
    void setSpawnTimer(const float spawnTimer);
    void setLevel(Level *l);
    // Methods
    void render(float deltaTime, sf::RenderWindow *w) const;
    void update(float deltaTime);
    void handleEvent(sf::Event &e);
    void exit();
};

#endif // WAVE_H
