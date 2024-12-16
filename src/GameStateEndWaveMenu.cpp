#include "GameStateEndWaveMenu.h"

GameStateEndWaveMenu::GameStateEndWaveMenu(GameState *state, GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    stateToPause = state;
    gameManager = gm;
    menu = std::make_unique<Menu>(w, f);
    menu->initEndWave(gm, state);
};

void GameStateEndWaveMenu::render(float deltaTime) const
{
    Player *p = gameManager->getPlayer();
    stateToPause->render(deltaTime);
    menu->render(deltaTime);
    menu->renderPlayerStats(p);
}

void GameStateEndWaveMenu::update(float deltaTime) const
{
}

void GameStateEndWaveMenu::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStateEndWaveMenu::pause() const
{
}

void GameStateEndWaveMenu::exit() const
{
}