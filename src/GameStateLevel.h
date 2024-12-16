#ifndef GAME_STATE_LEVEL_H
#define GAME_STATE_LEVEL_H

#include <memory>
#include "GameState.h"
#include "GameManager.h"
#include "Menu.h"
#include "Level.h"
#include <SFML/Graphics.hpp>

class GameStateLevel : public GameState
{
private:
    Level *lvl;
    std::unique_ptr<Menu> statsPlayer;

public:
    // Methods
    GameStateLevel(int l, GameManager *gm, sf::RenderWindow *w, sf::Font &f);
    void render(float deltaTime) const override;
    void update(float deltaTime) const override;
    void handleEvent(sf::Event &e) const override;
    void pause() const override;
    void exit() const override;
};

#endif // GAME_STATE_LEVEL_H