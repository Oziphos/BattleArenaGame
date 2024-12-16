#include "GameManager.h"
#include "GameStateMainMenu.h"
#include "Player.h"
#include <iostream>
#include <stdexcept>

// Constructors
GameManager::GameManager(sf::RenderWindow *w) : window(w)
{
    if (!globalFont.loadFromFile("../assets/fonts/COUR.TTF"))
    {
        throw std::runtime_error("Failed to load font: ../assets/fonts/COUR.TTF");
        std::exit(EXIT_FAILURE);
    }
    player = entityFactory->createPlayer();
    collisionHandler = std::make_unique<CollisionHandler>(w, player.get());
    entityFactory = std::make_unique<EntityFactory>();
}

// Getters
sf::RenderWindow *GameManager::getWindow() const
{
    return window;
}

sf::Font &GameManager::getFont() const
{
    return const_cast<sf::Font &>(globalFont);
}

CollisionHandler *GameManager::getCollisionHandler() const
{
    return collisionHandler.get();
}

EntityFactory *GameManager::getEntityFactory() const
{
    return entityFactory.get();
}

GameState *GameManager::getState() const
{
    return state;
}

Player *GameManager::getPlayer() const
{
    return player.get();
}

// Setters
void GameManager::setWindow(sf::RenderWindow *w)
{
    window = w;
}

void GameManager::setFont(const sf::Font &f)
{
    globalFont = f;
}

void GameManager::setCollisionHandler(std::unique_ptr<CollisionHandler> handler)
{
    collisionHandler = std::move(handler);
}

void GameManager::setEntityFactory(std::unique_ptr<EntityFactory> factory)
{
    entityFactory = std::move(factory);
}

void GameManager::setState(GameState *s)
{
    state = s;
}

void GameManager::setPlayer(std::unique_ptr<Player> p)
{
    player = std::move(p);
}

// Methods
void GameManager::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        state->handleEvent(event);
    }
}

void GameManager::update(float deltaTime)
{
    state->update(deltaTime);
}

void GameManager::render(float deltaTime)
{
    window->clear();
    state->render(deltaTime);
    /*
    // Dessine les entités
    for (const auto& entity : entityFactory->getEntities()) {
        window->draw(entity->getSprite());
    }
    */
    window->display();
}

void GameManager::run()
{
    sf::Clock clock;
    while (window->isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render(deltaTime);
    }
}
