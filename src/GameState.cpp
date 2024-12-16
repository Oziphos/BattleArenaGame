#include "GameState.h"

void GameState::setWindow(sf::RenderWindow * w) { window = w;}

void GameState::setFont(sf::Font& f) { font = f;}

sf::RenderWindow * GameState::getWindow() const { return window;}

sf::Font GameState::getFont() const { return font;}