#ifndef MENU_H
#define MENU_H

#include "MenuOption.h"
#include "GameManager.h"
#include "GameState.h"
#include <string>
#include <memory>
#include <vector>

class GameManager;

class Menu
{
private:
    sf::RenderWindow *window;
    sf::Font font;
    std::vector<std::unique_ptr<MenuOption>> options;
    sf::Texture menuTexture;
    sf::Sprite menuSprite;

public:
    // Constructors
    Menu(sf::RenderWindow *w, sf::Font &f);
    Menu(sf::RenderWindow *w, const sf::Font &f, const std::vector<std::unique_ptr<MenuOption>> &o);
    // Getters
    sf::RenderWindow *getWindow() const;
    const std::vector<std::unique_ptr<MenuOption>> &getOptions() const;
    // Setters
    void setWindow(sf::RenderWindow *w);
    void setOptions(std::vector<std::unique_ptr<MenuOption>> &&o);
    // Methods
    void addOption(std::unique_ptr<MenuOption> o);
    void handleEvent(sf::Event &e);
    void handleMove();
    void render(float deltaTime);
    void exit();
    void initMain(GameManager *g);
    void initLevels(GameManager *g);
    void initPause(GameManager *g, GameState *s);
    void initWin(GameManager *g, GameState *s);
    void initLoose(GameManager *g, GameState *s);
    void initEndWave(GameManager *g, GameState *s);
    void setOptionsPosition(std::vector<std::unique_ptr<MenuOption>> &o, const std::string &orientation = "vertical");
    void setBackground(const std::string &imagePath);
    void renderPlayerStats(Player *p) const;
    void renderPlayerLife(Player *p) const;
};

#endif // MENU_H