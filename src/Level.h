#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "Arena.h"
#include "Wave.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "GameManager.h"
#include "CollisionHandler.h"
#include <memory>
#include <vector>

class CollisionHandler;
class GameManager;
class Wave;

class Level
{
private:
    int levelId;
    Arena *arena;
    GameManager *gameManager;
    CollisionHandler *collisionHandler;
    sf::RenderWindow *window;
    sf::Font font;
    std::vector<std::unique_ptr<Wave>> waves;
    std::unique_ptr<Wave> actualWave;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<Projectile>> ennemyProjectiles;
    std::vector<std::unique_ptr<Projectile>> playerProjectiles;
    void updatePlayer(float deltaTime);
    void updateWaves(float deltaTime);
    void updateProjectiles(float deltaTime);
    void handleCollisions();
    void handleEnnemyProjectileCollisions(Projectile *projectile);
    void handlePlayerProjectileCollisions(Projectile *projectile);
    void cleanupProjectiles();
    void markProjectileForRemoval(Projectile *projectile);
    void win() const;
    void loose() const;

public:
    // Constructors
    Level(int lvlId, CollisionHandler *ch, GameManager *gm, sf::RenderWindow *w, sf::Font &f);
    // Getters
    int getLevelId() const;
    Arena *getArena() const;
    GameManager *getGameManager() const;
    CollisionHandler *getCollisionHandler() const;
    sf::RenderWindow *getWindow() const;
    sf::Font getFont() const;
    const std::vector<std::unique_ptr<Wave>> &getWaves() const;
    Wave *getActualWave() const;
    const std::vector<std::unique_ptr<Obstacle>> &getObstacles() const;
    // Setters
    void setLevelID(int id);
    void setGameManager(GameManager *gm);
    void setCollisionHandler(CollisionHandler *ch);
    void setArena(Arena *a);
    void setWindow(sf::RenderWindow *w);
    void setFont(sf::Font &f);
    void setWaves(std::vector<std::unique_ptr<Wave>> &&w);
    void setActualWave(std::unique_ptr<Wave> aw);
    void setObstacles(std::vector<std::unique_ptr<Obstacle>> &&o);
    // Methods
    void addWave(std::unique_ptr<Wave> w);
    void addObstacle(std::unique_ptr<Obstacle> o);
    void addEnnemyProjectile(std::unique_ptr<Projectile> p);
    void addPlayerProjectile(std::unique_ptr<Projectile> p);
    void removeProjectile(Projectile *p);
    void render(float deltaTime) const;
    void update(float deltaTime);
    void handleEvent(sf::Event &e) const;
    void pause() const;
    void exit() const;
    void init(int lvlId);
    void changeActualWave();
};

#endif // LEVEL_H