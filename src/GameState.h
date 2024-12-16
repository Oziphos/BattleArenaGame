#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>

class GameState
{
private:
    sf::RenderWindow *window;
    sf::Font font;

public:
    // Getters
    sf::RenderWindow *getWindow() const;
    sf::Font getFont() const;
    // Setters
    void setWindow(sf::RenderWindow *w);
    void setFont(sf::Font &f);
    // Methods
    virtual void render(float deltaTime) const = 0;
    virtual void update(float deltaTime) const = 0;
    virtual void handleEvent(sf::Event &e) const = 0;
    virtual void pause() const = 0;
    virtual void exit() const = 0;
    virtual ~GameState() {};
};

#endif // GAME_STATE_H