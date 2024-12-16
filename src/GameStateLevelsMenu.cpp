#include "GameStateLevelsMenu.h"

GameStateLevelsMenu::GameStateLevelsMenu(GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    menu = std::make_unique<Menu>(w, f);
    menu->initLevels(gm);
    menu->setBackground("../assets/images/menuBg.png");
}

void GameStateLevelsMenu::render(float deltaTime) const
{
    menu->render(deltaTime);
}

void GameStateLevelsMenu::update(float deltaTime) const
{
}

void GameStateLevelsMenu::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStateLevelsMenu::pause() const
{
}

void GameStateLevelsMenu::exit() const
{
}