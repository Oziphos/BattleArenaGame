#include "MenuOption.h"
#include "TextureCache.cpp"
#include <iostream>

// Constructors
MenuOption::MenuOption(const std::string &s, const sf::Vector2f &p, const sf::Font &f, std::function<void()> a, const std::string &imagePath)
    : position(p), font(f), action(a)
{
    // Text
    text.setFont(font);
    text.setString(s);
    text.setCharacterSize(32);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setPosition(p);

    if (!backgroundTexture.loadFromFile(imagePath))
    {
        throw std::runtime_error("Erreur: Impossible de charger l'image " + imagePath);
    }

    sf::Vector2f size(text.getLocalBounds().width + 30, text.getLocalBounds().height + 15);

    // Background
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale((size.x / backgroundTexture.getSize().x) + 3, (size.y / backgroundTexture.getSize().y) + 3);
    backgroundSprite.setPosition(p.x - ((backgroundTexture.getSize().x) / 2), p.y);

    // Rectangle
    buttonShape.setSize(size);
    buttonShape.setFillColor(sf::Color::Transparent);
    buttonShape.setOutlineThickness(2);
    buttonShape.setOutlineColor(sf::Color::Black);
    buttonShape.setPosition(p);
}

// Getters
sf::Font MenuOption::getFont() const
{
    return font;
}

sf::Text MenuOption::getText() const
{
    return text;
}

sf::RectangleShape MenuOption::getButtonShape() const
{
    return buttonShape;
}

std::function<void()> MenuOption::getAction() const
{
    return action;
}

sf::Vector2f MenuOption::getPosition() const
{
    return position;
}

sf::Texture MenuOption::getBackgroundTexture() const
{
    return backgroundTexture;
}

sf::Sprite MenuOption::getBackgroundSprite() const
{
    return backgroundSprite;
}

sf::FloatRect MenuOption::getOptionBounds() const
{
    return buttonShape.getGlobalBounds();
}

sf::FloatRect MenuOption::getSpriteBounds() const
{
    return backgroundSprite.getGlobalBounds();
}

// Setters
void MenuOption::setFont(sf::Font &f) { font = f; }

void MenuOption::setText(sf::Text &t) { text = t; }

void MenuOption::setButtonShape(sf::RectangleShape &b) { buttonShape = b; }

void MenuOption::setAction(std::function<void()> &a) { action = a; }

void MenuOption::setPosition(sf::Vector2f &pButton, sf::Vector2f &pTexture)
{
    position = pButton;
    buttonShape.setPosition(pButton);
    backgroundSprite.setPosition(pTexture);
    text.setPosition(pButton);
}

void MenuOption::setBackgroundTexture(sf::Texture &t)
{
    backgroundTexture = t;
}

void MenuOption::setBackgroundSprite(sf::Sprite &s)
{
    backgroundSprite = s;
}

// Methods
void MenuOption::render(sf::RenderWindow *window)
{
    window->draw(backgroundSprite);
    window->draw(buttonShape);
    window->draw(text);
}

void MenuOption::handleClick()
{
    if (action)
    {
        action();
    }
}

void MenuOption::handleHover(sf::RenderWindow *window)
{
    sf::Cursor c;
    if (c.loadFromSystem(sf::Cursor::Hand))
    {
        window->setMouseCursor(c);
    }
}