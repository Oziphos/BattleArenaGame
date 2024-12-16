#ifndef ARENA_H
#define ARENA_H

#include <SFML/Graphics.hpp>

class Arena {
    private:
        sf::RenderWindow * window;
        sf::Texture arenaTexture;
        sf::Sprite arenaSprite;
    public:
    // Constructors
    Arena(sf::RenderWindow * w, sf::Texture& t);
    // Getters
    sf::RenderWindow * getWindow();
    sf::Texture getArenaTexture() const;
    sf::Sprite getArenaSprite() const;
    // Setters
    void setWindow(sf::RenderWindow * w);
    void setArenaTexture(sf::Texture& t);
    void setArenaSprite(sf::Sprite& s);
    // Methods
    void render();
};

#endif //ARENA_H