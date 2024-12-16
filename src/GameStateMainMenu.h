#ifndef GAME_STATE_MAIN_MENU_H
#define GAME_STATE_MAIN_MENU_H

#include "GameState.h"
#include "GameManager.h"

class GameStateMainMenu : public GameState
{
private:
    std::unique_ptr<Menu> menu;

public:
    // Methods
    GameStateMainMenu(GameManager *gm, sf::RenderWindow *w, sf::Font f);
    void render(float deltaTime) const override;
    void update(float deltaTime) const override;
    void handleEvent(sf::Event &e) const override;
    void pause() const override;
    void exit() const override;
};

#endif // GAME_STATE_MAIN_MENU_H