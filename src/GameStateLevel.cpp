#include "GameStateLevel.h"
#include "Level.h"

GameStateLevel::GameStateLevel(int l, GameManager *gm, sf::RenderWindow *w, sf::Font &f)
{
    this->setWindow(w);
    this->setFont(f);
    lvl = new Level(l, gm->getCollisionHandler(), gm, w, f);
    (gm->getPlayer())->setLevel(lvl);
    statsPlayer = std::make_unique<Menu>(w, f);
};

void GameStateLevel::render(float deltaTime) const
{
    lvl->render(deltaTime);
    statsPlayer->renderPlayerLife(lvl->getGameManager()->getPlayer());
}

void GameStateLevel::update(float deltaTime) const
{
    lvl->update(deltaTime);
}

void GameStateLevel::handleEvent(sf::Event &e) const
{
    lvl->handleEvent(e);
}

void GameStateLevel::pause() const
{
    lvl->pause();
}

void GameStateLevel::exit() const
{
    lvl->exit();
}