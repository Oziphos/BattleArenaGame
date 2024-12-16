#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class MenuOption
{
private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape buttonShape;
    std::function<void()> action;
    sf::Vector2f position;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    // Constructors
    MenuOption(const std::string &string, const sf::Vector2f &position, const sf::Font &font, std::function<void()> action, const std::string &imagePath);
    // Getters
    sf::Font getFont() const;
    sf::Text getText() const;
    sf::RectangleShape getButtonShape() const;
    std::function<void()> getAction() const;
    sf::FloatRect getOptionBounds() const;
    sf::Vector2f getPosition() const;
    sf::Texture getBackgroundTexture() const;
    sf::Sprite getBackgroundSprite() const;
    sf::FloatRect getSpriteBounds() const;
    // Setters
    void setFont(sf::Font &f);
    void setText(sf::Text &t);
    void setButtonShape(sf::RectangleShape &b);
    void setAction(std::function<void()> &a);
    void setPosition(sf::Vector2f &pButton, sf::Vector2f &pTexture);
    void setBackgroundTexture(sf::Texture &t);
    void setBackgroundSprite(sf::Sprite &s);
    // Methods
    void render(sf::RenderWindow *w);
    void handleClick();
    void handleHover(sf::RenderWindow *w);
};

#endif // MENU_OPTION_H