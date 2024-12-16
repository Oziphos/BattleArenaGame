#ifndef GAME_STATE_PAUSE_H
#define GAME_STATE_PAUSE_H

#include <memory>
#include "GameState.h"
#include "GameManager.h"
#include "Menu.h"
#include "Level.h"
#include <SFML/Graphics.hpp>

class GameStatePause : public GameState
{
private:
    std::unique_ptr<Menu> menu;
    GameState *stateToPause;
    GameManager *gameManager;

public:
    // Methods
    GameStatePause(GameState *state, GameManager *gm, sf::RenderWindow *w, sf::Font &f);
    void render(float deltaTime) const override;
    void update(float deltaTime) const override;
    void handleEvent(sf::Event &e) const override;
    void pause() const override;
    void exit() const override;
};

#endif // GAME_STATE_PAUSE_H