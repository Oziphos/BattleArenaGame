#include "CollisionHandler.h"
#include <random>
#include <iostream>
// Constructor
CollisionHandler::CollisionHandler(sf::RenderWindow *w, Player *p) : window(w), player(p) {}

// Getters
Player *CollisionHandler::getPlayer() const { return player; }

sf::RenderWindow *CollisionHandler::getWindow() const
{
    return window;
}

// Setters
void CollisionHandler::setPlayer(Player *p) { player = p; }

void CollisionHandler::setWindow(sf::RenderWindow *w) { window = w; }

// Methods
void CollisionHandler::setSpawnPosition(Level *lvl, Entity *e)
{
    const int maxAttempts = 100;
    // Dimensions de l'arène
    sf::Vector2f arenaSize(1080, 900);
    const float gridStep = 200.0f;

    // Position par défaut si aucune place n'est trouvée
    sf::Vector2f defaultPosition(0, 0);

    // Parcourir la zone jouable par étapes (grille)
    for (int attempt = 0; attempt < maxAttempts; ++attempt)
    {
        // Générer une position aléatoire dans l'arène
        sf::Vector2f candidatePosition = generateRandomPosition(arenaSize.x, arenaSize.y);

        // Vérifier si la position est libre
        if ((isPositionFree(candidatePosition, lvl)) /*&& !isPositionInAttackRange(candidatePosition, player->getPosition(), player->getAttackRange())*/)
        {
            e->setGlobalPosition(candidatePosition); // Position trouvée, on la définit
            return;                                  // On arrête après avoir trouvé une position vali
        }
    }

    // Aucune position libre trouvée, on place à la position par défaut
    e->setGlobalPosition(defaultPosition);
}

bool CollisionHandler::isPositionFree(const sf::Vector2f &position, Level *lvl) const
{
    // Vérifier les obstacles
    for (const auto &obstacle : lvl->getObstacles())
    {
        if (obstacle->getSprite().getGlobalBounds().contains(position))
        {
            return false;
        }
    }

    // Vérifier les entités de la vague actuelle
    Wave *actualWave = lvl->getActualWave();
    if (actualWave)
    {
        for (const auto &ennemy : actualWave->getRenderableEnnemies())
        {
            if (ennemy->getSprite().getGlobalBounds().contains(position))
            {
                return false;
            }
        }
    }
    return true;
}

sf::Vector2f CollisionHandler::generateRandomPosition(float maxX, float maxY)
{
    static std::random_device rd;                         // générateur de nombres aléatoires basé sur l'horloge du système
    static std::mt19937 gen(rd());                        // générateur de nombres pseudo-aléatoires (Mersenne Twister)
    std::uniform_real_distribution<float> distX(0, maxX); // distribution uniforme sur [0, maxX]
    std::uniform_real_distribution<float> distY(0, maxY); // distribution uniforme sur [0, maxY]

    return sf::Vector2f(distX(gen), distY(gen)); // générer et retourner la position aléatoire
}

bool CollisionHandler::isPositionInAttackRange(const sf::Vector2f &candidatePosition, const sf::Vector2f &playerPosition, float attackRange)
{
    // Calcul de la distance entre la position candidate et la position du joueur
    float distance = std::sqrt(std::pow(candidatePosition.x - playerPosition.x, 2) + std::pow(candidatePosition.y - playerPosition.y, 2));

    // Retourner vrai si la distance est inférieure ou égale à la portée d'attaque
    return distance <= attackRange;
}

bool CollisionHandler::checkCollision(Entity *a, Entity *b)
{
    const auto &bounds1 = a->getSprite().getGlobalBounds();
    const auto &bounds2 = b->getSprite().getGlobalBounds();
    return bounds1.intersects(bounds2);
}

void CollisionHandler::resolveCollision(Entity *a, Entity *b)
{
    if (Obstacle *obstacle = dynamic_cast<Obstacle *>(b))
    {
        // Annule le mouvement du joueur si collision avec un obstacle
        a->setGlobalPosition(a->getPreviousPosition());
    }
}