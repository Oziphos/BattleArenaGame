#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "CollisionHandler.h"
#include "EntityFactory.h"
#include "Menu.h"
#include "GameState.h"
#include "Player.h"

class GameState;
class Menu;
class EntityFactory;

class GameManager
{
private:
    sf::RenderWindow *window;
    sf::Font globalFont;
    std::unique_ptr<CollisionHandler> collisionHandler;
    std::unique_ptr<EntityFactory> entityFactory;
    GameState *state;
    std::unique_ptr<Player> player;

public:
    // Constructors
    GameManager(sf::RenderWindow *w);

    // Getters
    sf::RenderWindow *getWindow() const;
    sf::Font &getFont() const;
    CollisionHandler *getCollisionHandler() const;
    EntityFactory *getEntityFactory() const;
    GameState *getState() const;
    Player *getPlayer() const;

    // Setters
    void setWindow(sf::RenderWindow *w);
    void setFont(const sf::Font &f);
    void setCollisionHandler(std::unique_ptr<CollisionHandler> handler);
    void setEntityFactory(std::unique_ptr<EntityFactory> factory);
    void setState(GameState *s);
    void setPlayer(std::unique_ptr<Player> p);

    // Methods
    void handleEvents();
    void update(float deltaTime);
    void render(float deltaTime);
    void run();
};

#endif // GAME_MANAGER_H
