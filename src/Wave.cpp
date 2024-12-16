#include "Wave.h"
#include "EnnemySoldier.h"
#include "CollisionHandler.h"
#include <cstdlib>
#include <iostream>

// Constructors
Wave::Wave(Level *l, int lvlId, int waveNb, Player *p) : lvl(l)
{
    int nbEnnemies = this->calculateBaseEnemyCount(lvlId, waveNb);
    std::cout << "Creating wave for Level : " << lvlId << " and wave n° : " << waveNb << std::endl;
    std::cout << "Total ennemies created : " << nbEnnemies << std::endl;

    for (int i = 0; i < nbEnnemies; i++)
    {
        // Générer un nombre aléatoire entre 0 et RAND_MAX
        int randomChance = rand();

        // Si la chance est inférieure à 30% de RAND_MAX, crée un EnnemyMarksman, sinon un EnnemySoldier
        if (randomChance < (0.2 * RAND_MAX))
        {
            ennemies.push_back(factory->createEnnemyMarksman(l, p, lvlId, waveNb));
        }
        else
        {
            ennemies.push_back(factory->createEnnemySoldier(l, p, lvlId, waveNb));
        }
    }
}

// Getters
const std::vector<std::unique_ptr<Ennemy>> &Wave::getEnnemies() const
{
    return ennemies;
}

const std::vector<std::unique_ptr<Ennemy>> &Wave::getRenderableEnnemies() const
{
    return renderableEnnnemies;
}

EntityFactory *Wave::getFactory() const { return factory; }

CollisionHandler *Wave::getCollisionHandler() const
{
    return collisionHandler;
}

Level *Wave::getLevel() const
{
    return lvl;
}

// Setters
void Wave::setEnnemies(std::vector<std::unique_ptr<Ennemy>> &&e)
{
    ennemies = std::move(e);
}

void Wave::setRenderableEnnemies(std::vector<std::unique_ptr<Ennemy>> &&e)
{
    renderableEnnnemies = std::move(e);
}

void Wave::setFactory(EntityFactory *f) { factory = f; }

void Wave::setCollisionHandler(CollisionHandler *ch)
{
    collisionHandler = ch;
}

void Wave::setLevel(Level *l)
{
    lvl = l;
}

// Methods
void Wave::render(float deltaTime, sf::RenderWindow *window) const
{
    for (const auto &ennemy : renderableEnnnemies)
    {
        ennemy->render(deltaTime, window);
    }
}

void Wave::update(float deltaTime)
{

    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval && !ennemies.empty())
    {
        std::unique_ptr<Ennemy> e = std::move(ennemies.back());
        ennemies.pop_back();
        collisionHandler->setSpawnPosition(lvl, e.get());
        renderableEnnnemies.push_back(std::move(e));

        spawnTimer -= spawnInterval;
    }

    for (const auto &ennemy : renderableEnnnemies)
    {
        ennemy->update(deltaTime);
    }
}

void Wave::handleEvent(sf::Event &e)
{
}

void Wave::exit()
{
}

int Wave::calculateBaseEnemyCount(int lvlId, int waveNb) const
{
    return 5 + lvlId * 2 + (waveNb + 1) * 3;
}