#include "GameStateLevelLoose.h"

GameStateLevelLoose::GameStateLevelLoose(GameState *state, GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    stateToPause = state;
    menu = std::make_unique<Menu>(w, f);
    menu->initLoose(gm, state);
};

void GameStateLevelLoose::render(float deltaTime) const
{
    stateToPause->render(deltaTime);
    menu->render(deltaTime);
}

void GameStateLevelLoose::update(float deltaTime) const
{
}

void GameStateLevelLoose::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStateLevelLoose::pause() const
{
}

void GameStateLevelLoose::exit() const
{
}