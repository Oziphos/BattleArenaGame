#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "GameStateMainMenu.h"
#include "Player.h"

int main()
{
    // Window initialisation
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Andalore", sf::Style::Fullscreen);

    // Window framerate limit
    window.setFramerateLimit(60);
    GameManager gameManager(&window);
    // Waiting for gameManager to be created before setting the state because its need a GameManager Object
    gameManager.setState(new GameStateMainMenu(&gameManager, gameManager.getWindow(), gameManager.getFont()));

    gameManager.run();
    return 0;
}