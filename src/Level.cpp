#include "Level.h"
#include "Player.h"
#include "GameManager.h"
#include "GameStateLevelsMenu.h"
#include "GameStatePause.h"
#include "GameStateLevelWin.h"
#include "GameStateLevelLoose.h"
#include "GameStateEndWaveMenu.h"
#include <iostream>

Level::Level(int lvlId, CollisionHandler *ch, GameManager *gm, sf::RenderWindow *w, sf::Font &f) : window(w), font(f), collisionHandler(ch), gameManager(gm)
{
    gm->setPlayer(gm->getEntityFactory()->createPlayer());
    levelId = lvlId;
    sf::Texture t;
    std::string lvlIdString = std::to_string(lvlId);
    const std::string &imagePath = "../assets/images/lvl" + lvlIdString + ".png";
    if (!t.loadFromFile(imagePath))
    {
        throw std::runtime_error("Erreur: Impossible de charger l'image " + imagePath);
    }
    arena = new Arena(window, t);
    this->init(lvlId);
    actualWave = std::move(waves.back());
    waves.pop_back();
}

int Level::getLevelId() const { return levelId; }

Arena *Level::getArena() const { return arena; }

GameManager *Level::getGameManager() const { return gameManager; }

CollisionHandler *Level::getCollisionHandler() const
{
    return collisionHandler;
}

sf::RenderWindow *Level::getWindow() const { return window; }

sf::Font Level::getFont() const { return font; }

const std::vector<std::unique_ptr<Wave>> &Level::getWaves() const
{
    return waves;
}

Wave *Level::getActualWave() const { return actualWave.get(); }

const std::vector<std::unique_ptr<Obstacle>> &Level::getObstacles() const
{
    return obstacles;
}

// Setters
void Level::setLevelID(int id) { levelId = id; }

void Level::setGameManager(GameManager *gm) { gameManager = gm; }

void Level::setCollisionHandler(CollisionHandler *ch)
{
    collisionHandler = ch;
}

void Level::setArena(Arena *a) { arena = a; }

void Level::setWindow(sf::RenderWindow *w) { window = w; }

void Level::setFont(sf::Font &f) { font = f; }

void Level::setWaves(std::vector<std::unique_ptr<Wave>> &&w)
{
    waves = std::move(w);
}

void Level::setActualWave(std::unique_ptr<Wave> w)
{
    actualWave = std::move(w);
}

void Level::setObstacles(std::vector<std::unique_ptr<Obstacle>> &&o)
{
    obstacles = std::move(o);
}

// Methods
void Level::addWave(std::unique_ptr<Wave> wave)
{
    waves.push_back(std::move(wave));
}

void Level::addObstacle(std::unique_ptr<Obstacle> o)
{
    obstacles.push_back(std::move(o));
}

void Level::addEnnemyProjectile(std::unique_ptr<Projectile> p)
{
    ennemyProjectiles.push_back(std::move(p));
}

void Level::addPlayerProjectile(std::unique_ptr<Projectile> p)
{
    playerProjectiles.push_back(std::move(p));
}

void Level::removeProjectile(Projectile *p)
{
    auto itEnnemy = std::remove_if(ennemyProjectiles.begin(), ennemyProjectiles.end(),
                                   [p](const std::unique_ptr<Projectile> &proj)
                                   {
                                       return proj.get() == p;
                                   });

    if (itEnnemy != ennemyProjectiles.end())
    {
        ennemyProjectiles.erase(itEnnemy, ennemyProjectiles.end());
    }

    auto itPlayer = std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
                                   [p](const std::unique_ptr<Projectile> &proj)
                                   {
                                       return proj.get() == p;
                                   });

    if (itPlayer != playerProjectiles.end())
    {
        playerProjectiles.erase(itPlayer, playerProjectiles.end());
    }
}

void Level::render(float deltaTime) const
{
    arena->render();
    for (const auto &obstacle : obstacles)
    {
        obstacle->render(deltaTime, window);
    }

    (actualWave.get())->render(deltaTime, window);
    Player *p = gameManager->getPlayer();
    p->render(deltaTime, window);

    for (const auto &projectile : playerProjectiles)
    {
        projectile->render(deltaTime, window);
    }

    for (const auto &projectile : ennemyProjectiles)
    {
        projectile->render(deltaTime, window);
    }
}

void Level::update(float deltaTime)
{
    // Mise à jour des composants principaux
    this->updatePlayer(deltaTime);
    this->updateWaves(deltaTime);
    this->updateProjectiles(deltaTime);

    // Gestion des collisions
    this->handleCollisions();

    // Suppression des projectiles inutilisés
    this->cleanupProjectiles();
}

void Level::updatePlayer(float deltaTime)
{
    Player *player = gameManager->getPlayer();
    if (player->isAlive())
    {
        player->update(deltaTime);
    }
    else
    {
        this->loose();
    }
}

void Level::updateWaves(float deltaTime)
{
    if (actualWave)
    {
        actualWave->update(deltaTime);

        for (const auto &ennemy : actualWave->getRenderableEnnemies())
        {
            if (ennemy->isAlive())
            {
                return;
            }
        }
        if (actualWave->getEnnemies().empty())
        {
            gameManager->setState(
                new GameStateEndWaveMenu(
                    gameManager->getState(),
                    gameManager,
                    gameManager->getWindow(),
                    gameManager->getFont()));
        }
    }
}

void Level::updateProjectiles(float deltaTime)
{
    for (const auto &projectile : ennemyProjectiles)
    {
        projectile->update(deltaTime);
    }

    for (auto &projectile : playerProjectiles)
    {
        projectile->update(deltaTime);
    }
}

void Level::handleCollisions()
{
    Player *player = gameManager->getPlayer();

    // Collisions joueur-obstacles
    for (const auto &obstacle : obstacles)
    {
        if (collisionHandler->checkCollision(player, obstacle.get()))
        {
            collisionHandler->resolveCollision(player, obstacle.get());
        }
    }

    // Collisions projectiles
    for (auto &projectile : ennemyProjectiles)
    {
        handleEnnemyProjectileCollisions(projectile.get());
    }

    for (auto &projectile : playerProjectiles)
    {
        handlePlayerProjectileCollisions(projectile.get());
    }
}

void Level::handleEnnemyProjectileCollisions(Projectile *projectile)
{
    // Collisions avec les obstacles
    for (const auto &obstacle : obstacles)
    {
        if (collisionHandler->checkCollision(projectile, obstacle.get()))
        {
            collisionHandler->resolveCollision(projectile, obstacle.get());
            projectile->setPenetration(projectile->getPenetration() - 1);

            if (projectile->getPenetration() <= 0)
            {
                markProjectileForRemoval(projectile);
                return;
            }
        }
    }

    // Collisions avec le joueur
    Player *player = this->getGameManager()->getPlayer();
    if (collisionHandler->checkCollision(projectile, player))
    {
        collisionHandler->resolveCollision(projectile, player);
        player->defendAgainstEntity(projectile);

        projectile->setPenetration(projectile->getPenetration() - 1);
        if (projectile->getPenetration() <= 0)
        {
            markProjectileForRemoval(projectile);
            return;
        }
    }
}

void Level::handlePlayerProjectileCollisions(Projectile *projectile)
{
    // Collisions avec les obstacles
    for (const auto &obstacle : obstacles)
    {
        if (collisionHandler->checkCollision(projectile, obstacle.get()))
        {
            collisionHandler->resolveCollision(projectile, obstacle.get());
            projectile->setPenetration(projectile->getPenetration() - 1);

            if (projectile->getPenetration() <= 0)
            {
                markProjectileForRemoval(projectile);
                return;
            }
        }
    }

    // Collisions avec les ennemis
    for (const auto &enemy : actualWave->getRenderableEnnemies())
    {
        if (enemy->isAlive() && collisionHandler->checkCollision(projectile, enemy.get()))
        {
            collisionHandler->resolveCollision(projectile, enemy.get());
            enemy->defendAgainstEntity(projectile);

            projectile->setPenetration(projectile->getPenetration() - 1);
            if (projectile->getPenetration() <= 0)
            {
                markProjectileForRemoval(projectile);
                return;
            }
        }
    }
}

void Level::cleanupProjectiles()
{
    ennemyProjectiles.erase(
        std::remove_if(ennemyProjectiles.begin(), ennemyProjectiles.end(),
                       [](const std::unique_ptr<Projectile> &proj)
                       {
                           return proj->isOutOfBounds() || proj->isMarkedForRemoval();
                       }),
        ennemyProjectiles.end());

    playerProjectiles.erase(
        std::remove_if(playerProjectiles.begin(), playerProjectiles.end(),
                       [](const std::unique_ptr<Projectile> &proj)
                       {
                           return proj->isOutOfBounds() || proj->isMarkedForRemoval();
                       }),
        playerProjectiles.end());
}

void Level::markProjectileForRemoval(Projectile *projectile)
{
    projectile->markForRemoval(); // Ajoutez une méthode pour marquer un projectile
}

void Level::handleEvent(sf::Event &e) const
{
    // Vérifier si une touche est pressée
    if (e.type == sf::Event::KeyPressed)
    {
        // Si c'est la touche Échap
        if (e.key.code == sf::Keyboard::Escape)
        {
            pause(); // Mettre en pause
        }
    }
}

void Level::pause() const
{
    // Afficher un menu de pause ou changer l'état du jeu
    gameManager->setState(
        new GameStatePause(
            gameManager->getState(), // Supposons que vous ayez un état dédié au menu de pause
            gameManager,
            gameManager->getWindow(),
            gameManager->getFont()));
}

void Level::exit() const
{
    gameManager->setState(
        new GameStateLevelsMenu(
            gameManager,
            gameManager->getWindow(),
            gameManager->getFont()));
}

void Level::init(int lvlId)
{

    for (int i = 0; i < (10 * lvlId); i++)
    {
        waves.push_back(std::make_unique<Wave>(this, lvlId, i, gameManager->getPlayer()));
    }

    for (int i = 0; i < 2; i++)
    {
        auto o = std::make_unique<Obstacle>(this, sf::Vector2f(0, 0), true, false);
        collisionHandler->setSpawnPosition(this, o.get());
        obstacles.push_back(std::move(o));
    }
}

void Level::changeActualWave()
{
    if (!waves.empty())
    {
        actualWave = std::move(waves.front());
        waves.erase(waves.begin());
    }
    else
    {
        this->win();
    }
}

void Level::win() const
{
    gameManager->setState(
        new GameStateLevelWin(
            gameManager->getState(),
            gameManager,
            gameManager->getWindow(),
            gameManager->getFont()));
}

void Level::loose() const
{
    gameManager->setState(
        new GameStateLevelLoose(
            gameManager->getState(),
            gameManager,
            gameManager->getWindow(),
            gameManager->getFont()));
}
