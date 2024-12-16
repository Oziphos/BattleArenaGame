#include "GameStateLevelWin.h"

GameStateLevelWin::GameStateLevelWin(GameState *state, GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    stateToPause = state;
    menu = std::make_unique<Menu>(w, f);
    menu->initWin(gm, state);
};

void GameStateLevelWin::render(float deltaTime) const
{
    stateToPause->render(deltaTime);
    menu->render(deltaTime);
}

void GameStateLevelWin::update(float deltaTime) const
{
}

void GameStateLevelWin::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStateLevelWin::pause() const
{
}

void GameStateLevelWin::exit() const
{
}