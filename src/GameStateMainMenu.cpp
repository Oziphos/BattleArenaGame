#include "GameStateMainMenu.h"
#include <iostream>

GameStateMainMenu::GameStateMainMenu(GameManager *gm, sf::RenderWindow *w, sf::Font f)
{
    this->setWindow(w);
    this->setFont(f);
    menu = std::make_unique<Menu>(w, f);
    menu->initMain(gm);
    menu->setBackground("../assets/images/menuBg.png");
}

void GameStateMainMenu::render(float deltaTime) const
{
    menu->render(deltaTime);
}

void GameStateMainMenu::update(float deltaTime) const
{
}

void GameStateMainMenu::handleEvent(sf::Event &e) const
{
    menu->handleEvent(e);
}

void GameStateMainMenu::pause() const
{
}

void GameStateMainMenu::exit() const
{
    std::exit(EXIT_SUCCESS);
}