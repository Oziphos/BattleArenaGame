#ifndef GAME_STATE_LEVELS_MENU_H
#define GAME_STATE_LEVELS_MENU_H

#include <memory>
#include "GameState.h"
#include "Menu.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class GameStateLevelsMenu : public GameState
{
private:
    std::unique_ptr<Menu> menu;

public:
    // Methods
    GameStateLevelsMenu(GameManager *gm, sf::RenderWindow *w, sf::Font &f);
    void render(float deltaTime) const override;
    void update(float deltaTime) const override;
    void handleEvent(sf::Event &e) const override;
    void pause() const override;
    void exit() const override;
};

#endif // GAME_STATE_LEVELS_MENU_H