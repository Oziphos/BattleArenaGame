#include "Menu.h"
#include "MenuOption.h"
#include "GameManager.h"
#include "GameStateMainMenu.h"
#include "GameStateLevelsMenu.h"
#include "GameStateLevel.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Default Constructor
Menu::Menu(sf::RenderWindow *w, sf::Font &f) : window(w), font(f)
{
}

// Constructor with options
Menu::Menu(sf::RenderWindow *w, const sf::Font &f, const std::vector<std::unique_ptr<MenuOption>> &o) : window(w), font(f)
{
    for (const auto &option : o)
    {
        options.push_back(std::make_unique<MenuOption>(*option));
    }
}

// Getters
const std::vector<std::unique_ptr<MenuOption>> &Menu::getOptions() const
{
    return options;
}

// Setters
void Menu::setOptions(std::vector<std::unique_ptr<MenuOption>> &&o)
{
    options = std::move(o);
}

// Methods
void Menu::handleEvent(sf::Event &e)
{
    // Click on option
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            for (const auto &option : options)
            {
                if (option->getOptionBounds().contains(mousePos.x, mousePos.y))
                {
                    option->handleClick();
                    return;
                }
            }
        }
    }
    else if (e.type == sf::Event::MouseMoved)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        for (const auto &option : options)
        {
            if (option->getOptionBounds().contains(mousePos.x, mousePos.y))
            {
                option->handleHover(window);
                return;
            }
        }
        handleMove();
    }
}

void Menu::handleMove()
{
    sf::Cursor c;
    if (c.loadFromSystem(sf::Cursor::Arrow))
    {
        window->setMouseCursor(c);
    }
}

void Menu::render(float deltaTime)
{
    if (menuSprite.getTexture() != nullptr)
    {
        window->draw(menuSprite);
    }
    for (const auto &option : options)
    {
        option->render(window);
    }
}

void Menu::exit()
{
}

void Menu::addOption(std::unique_ptr<MenuOption> option)
{
    options.push_back(std::move(option));
}

void Menu::initMain(GameManager *gm)
{
    // Init options
    auto playOption = std::make_unique<MenuOption>(
        "Play",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateLevelsMenu(gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitOption = std::make_unique<MenuOption>(
        "Exit",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::exit(EXIT_SUCCESS); },
        "../assets/images/menuOption.png");
    // Set menu
    this->addOption(std::move(playOption));
    this->addOption(std::move(exitOption));
    this->setOptionsPosition(options);
}

void Menu::initLevels(GameManager *gm)
{
    // Init options
    auto lvl1 = std::make_unique<MenuOption>(
        "1",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateLevel(1, gm, this->window, this->font)); },
        "../assets/images/lvlOption.png");
    auto lvl2 = std::make_unique<MenuOption>(
        "2",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::cout << "Hello depuis lvl2 !" << std::endl; },
        "../assets/images/lvlOption.png");

    auto lvl3 = std::make_unique<MenuOption>(
        "3",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::cout << "Hello depuis lvl3 !" << std::endl; },
        "../assets/images/lvlOption.png");

    auto back = std::make_unique<MenuOption>(
        "Back",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateMainMenu(gm, this->window, this->font)); },
        "../assets/images/backOption.png");

    this->addOption(std::move(lvl1));
    this->addOption(std::move(lvl2));
    this->addOption(std::move(lvl3));

    this->setOptionsPosition(options, "horizontal");

    sf::Vector2f topLeft(0, 0);
    sf::Vector2f a((back->getSpriteBounds().width / 2) - (back->getOptionBounds().width / 2), (back->getSpriteBounds().height / 2) - (back->getOptionBounds().height / 2));
    back->setPosition(a, topLeft);
    this->addOption(std::move(back));
}

void Menu::initPause(GameManager *gm, GameState *state)
{
    // Init options
    auto resumeOption = std::make_unique<MenuOption>(
        "Resume",
        sf::Vector2f(0, 0),
        font,
        [gm, state]()
        { gm->setState(state); },
        "../assets/images/menuOption.png");
    auto restartOption = std::make_unique<MenuOption>(
        "Restart",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateLevel(gm->getPlayer()->getLevel()->getLevelId(), gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitToMainMenuOption = std::make_unique<MenuOption>(
        "Exit level",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateMainMenu(gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitOption = std::make_unique<MenuOption>(
        "Exit game",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::exit(EXIT_SUCCESS); },
        "../assets/images/menuOption.png");
    // Set menu
    this->addOption(std::move(resumeOption));
    this->addOption(std::move(restartOption));
    this->addOption(std::move(exitToMainMenuOption));
    this->addOption(std::move(exitOption));
    this->setOptionsPosition(options);
}

void Menu::initWin(GameManager *gm, GameState *state)
{
    // Init options
    auto exitToMainMenuOption = std::make_unique<MenuOption>(
        "Exit level",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateMainMenu(gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitOption = std::make_unique<MenuOption>(
        "Exit game",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::exit(EXIT_SUCCESS); },
        "../assets/images/menuOption.png");
    // Set menu
    this->addOption(std::move(exitToMainMenuOption));
    this->addOption(std::move(exitOption));
    this->setOptionsPosition(options);
}

void Menu::initLoose(GameManager *gm, GameState *state)
{
    // Init options
    auto restartOption = std::make_unique<MenuOption>(
        "Restart",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateLevel(gm->getPlayer()->getLevel()->getLevelId(), gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitToMainMenuOption = std::make_unique<MenuOption>(
        "Exit level",
        sf::Vector2f(0, 0),
        font,
        [this, gm]()
        { gm->setState(new GameStateMainMenu(gm, this->window, this->font)); },
        "../assets/images/menuOption.png");
    auto exitOption = std::make_unique<MenuOption>(
        "Exit game",
        sf::Vector2f(0, 0),
        font,
        []()
        { std::exit(EXIT_SUCCESS); },
        "../assets/images/menuOption.png");
    // Set menu
    this->addOption(std::move(restartOption));
    this->addOption(std::move(exitToMainMenuOption));
    this->addOption(std::move(exitOption));
    this->setOptionsPosition(options);
}

void Menu::initEndWave(GameManager *gm, GameState *state)
{
    Player *p = gm->getPlayer();
    // Init options
    auto hitPointsOption = std::make_unique<MenuOption>(
        "HitPoints",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setHitPoints(p->getHitPoints() + 10);
            p->setMaxHitPoints(p->getMaxHitPoints() + 10);
            gm->setState(state);
            p->getLevel()
                ->changeActualWave();
        },
        "../assets/images/menuOption.png");
    auto armorOption = std::make_unique<MenuOption>(
        "Armor",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setArmor(p->getArmor() + 2);
            gm->setState(state);
            p->getLevel()->changeActualWave();
        },
        "../assets/images/menuOption.png");
    auto speedOption = std::make_unique<MenuOption>(
        "Speed",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setSpeed(p->getSpeed() + 10);
            gm->setState(state);
            p->getLevel()->changeActualWave();
        },
        "../assets/images/menuOption.png");
    auto attackOption = std::make_unique<MenuOption>(
        "Attack",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setAttack(p->getAttack() + 10);
            gm->setState(state);
            p->getLevel()
                ->changeActualWave();
        },
        "../assets/images/menuOption.png");
    auto attackSpeedOption = std::make_unique<MenuOption>(
        "Attack Speed",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setAttackSpeed(p->getAttackSpeed() + 1.0f);
            gm->setState(state);
            p->getLevel()->changeActualWave();
        },
        "../assets/images/menuOption.png");
    auto attackRangeOption = std::make_unique<MenuOption>(
        "Attack Range",
        sf::Vector2f(0, 0),
        font,
        [p, gm, state]()
        {
            p->setAttackRange(p->getAttackRange() + 50);
            gm->setState(state);
            p->getLevel()->changeActualWave();
        },
        "../assets/images/menuOption.png");
    // Set menu
    this->addOption(std::move(hitPointsOption));
    this->addOption(std::move(armorOption));
    this->addOption(std::move(speedOption));
    this->addOption(std::move(attackOption));
    this->addOption(std::move(attackSpeedOption));
    this->addOption(std::move(attackRangeOption));
    ;
    this->setOptionsPosition(options);
}

void Menu::setOptionsPosition(std::vector<std::unique_ptr<MenuOption>> &o, const std::string &orientation)
{
    int nbOptions = o.size();
    if (nbOptions > 0)
    {
        sf::Vector2u windowSize = (*window).getSize();
        int i = 0;
        for (const auto &option : o)
        {
            float optionWidth = option->getOptionBounds().width;
            float spriteWidth = option->getSpriteBounds().width;
            float optionHeight = option->getOptionBounds().height;
            float spriteHeight = option->getSpriteBounds().height;

            float optionPositionHorizontal;
            float optionPositionVertical;
            float spritePositionHorizontal;
            float spritePositionVertical;

            if (orientation == "vertical")
            {
                optionPositionHorizontal = (windowSize.x - optionWidth) / 2.f;
                optionPositionVertical = ((windowSize.y - optionHeight) / 2.f) + (i * 3 * optionHeight) - ((nbOptions - 1) * optionHeight);

                spritePositionHorizontal = (windowSize.x - spriteWidth) / 2.f;
                spritePositionVertical = ((windowSize.y - spriteHeight) / 2.f) + (i * 3 * optionHeight) - ((nbOptions - 1) * optionHeight);
            }
            else if (orientation == "horizontal")
            {
                optionPositionHorizontal = ((windowSize.x - optionWidth) / 2.f) + (i * 3 * optionWidth) - ((nbOptions - 1) * optionWidth);
                optionPositionVertical = (windowSize.y - optionHeight) / 2.f;

                spritePositionHorizontal = (windowSize.x - spriteWidth) / 2.f + (i * 3 * optionWidth) - ((nbOptions - 1) * optionWidth);
                spritePositionVertical = ((windowSize.y - spriteHeight) / 2.f);
            }

            sf::Vector2f optionPosition(optionPositionHorizontal, optionPositionVertical);
            sf::Vector2f spritePosition(spritePositionHorizontal, spritePositionVertical);

            option->setPosition(optionPosition, spritePosition);
            i++;
        }
    }
}

void Menu::setBackground(const std::string &imagePath)
{
    if (!menuTexture.loadFromFile(imagePath))
    {
        throw std::runtime_error("Erreur: Impossible de charger l'image " + imagePath);
    }
    menuSprite.setTexture(menuTexture);
    sf::Vector2u textureSize = menuTexture.getSize();
    sf::Vector2u windowSize = window->getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    menuSprite.setScale(scaleX, scaleY);
}

void Menu::renderPlayerStats(Player *p) const
{
    if (!p)
    {
        return;
    }
    // Préparer les textes à afficher
    sf::Text statsText;
    statsText.setFont(this->font);            // Assumez que 'Menu' a un membre 'font' de type sf::Font
    statsText.setCharacterSize(32);           // Taille du texte
    statsText.setFillColor(sf::Color::White); // Couleur du texte

    // Construire le texte des statistiques
    std::ostringstream statsStream;
    statsStream << "-- Player Stats --\n"
                << "HitPoints: " << p->getHitPoints() << "/" << p->getMaxHitPoints() << "\n"
                << "Armor: " << p->getArmor() << "\n"
                << "Speed: " << p->getSpeed() << "\n"
                << "Attack: " << p->getAttack() << "\n"
                << "Attack Speed: " << p->getAttackSpeed() << "\n"
                << "Attack Range: " << p->getAttackRange() << "\n"
                << "Projectile Speed: " << p->getProjectileSpeed() << "\n";

    statsText.setString(statsStream.str());

    // Positionnement du texte dans la fenêtre (par exemple en haut à gauche)
    statsText.setPosition(10.f, 10.f);

    // Rendu du texte dans la fenêtre
    this->window->draw(statsText);
}

void Menu::renderPlayerLife(Player *p) const
{
    if (!p)
    {
        return;
    }

    sf::Text lifeText;
    lifeText.setFont(this->font);
    lifeText.setCharacterSize(40);           // Taille du texte
    lifeText.setFillColor(sf::Color::White); // Couleur du texte

    // Construire le texte des points de vie
    std::ostringstream lifeStream;
    lifeStream << "HP: " << p->getHitPoints() << "/" << p->getMaxHitPoints();
    lifeText.setString(lifeStream.str());

    // Obtenir la taille de la fenêtre pour positionner le texte en bas à droite
    sf::Vector2u windowSize = this->window->getSize();
    sf::FloatRect textBounds = lifeText.getLocalBounds();

    // Calculer la position en bas à droite
    float xPosition = static_cast<float>(windowSize.x) - textBounds.width - 50.f;
    float yPosition = static_cast<float>(windowSize.y) - textBounds.height - 50.f;

    // Appliquer la position calculée
    lifeText.setPosition(xPosition, yPosition);

    // Dessiner le texte sur la fenêtre
    this->window->draw(lifeText);
}
