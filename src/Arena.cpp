#include "Arena.h"
#include <iostream>

Arena::Arena(sf::RenderWindow * w, sf::Texture& t) : window(w), arenaTexture(t) {
    arenaSprite.setTexture(arenaTexture);
    // Setting Texture for a fullscreen render
    sf::Vector2u textureSize = arenaTexture.getSize(); 
    sf::Vector2u windowSize = window->getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    arenaSprite.setScale(scaleX, scaleY);
};

sf::Texture Arena::getArenaTexture() const { return arenaTexture; }

sf::Sprite Arena::getArenaSprite() const { return arenaSprite; }

void Arena::setArenaTexture(sf::Texture& t) { arenaTexture = t; }

void Arena::setArenaSprite(sf::Sprite& s) { arenaSprite = s; }

void Arena::render() {
    window->draw(arenaSprite);
}