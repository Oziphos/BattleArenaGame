#include "GameStatePause.h"

GameStatePause::GameStatePause(GameState *state, GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    stateToPause = state;
    gameManager = gm;
    menu = std::make_unique<Menu>(w, f);
    menu->initPause(gm, state);
};

void GameStatePause::render(float deltaTime) const
{
    Player *p = gameManager->getPlayer();
    stateToPause->render(deltaTime);
    menu->render(deltaTime);
    menu->renderPlayerStats(p);
}

void GameStatePause::update(float deltaTime) const
{
}

void GameStatePause::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStatePause::pause() const
{
}

void GameStatePause::exit() const
{
}