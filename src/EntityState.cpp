#include "Entity.h"
#include "TextureCache.cpp"
#include "EntityState.h"
#include <iostream>
// Constructors
// Getters
const std::vector<std::shared_ptr<sf::Texture>> &EntityState::getTextures() const
{
    return entityTextures;
}

std::size_t EntityState::getCurrentTextureIndex() const
{
    return currentTextureIndex;
}

float EntityState::getAnimationTimer() const { return animationTimer; }

float EntityState::getAnimationChangeInterval() const { return animationChangeInterval; }

sf::Sprite EntityState::getSprite() const { return entitySprite; }

float EntityState::getRotation() const { return rotation; }

sf::Vector2f EntityState::getPosition() const { return position; }

// Setters
void EntityState::setTextures(std::vector<std::shared_ptr<sf::Texture>> &&t)
{
    entityTextures = std::move(t);
}

void EntityState::setCurrrentTextureIndex(const std::size_t &i)
{
    currentTextureIndex = i;
}

void EntityState::setAnimationTimer(const float &at) { animationTimer = at; }

void EntityState::setAnimationChangeInterval(const float &ac)
{
    animationChangeInterval = ac;
}

void EntityState::setSprite(const sf::Sprite &s) { entitySprite = s; }

void EntityState::setRotation(const float &r) { rotation = r; }

void EntityState::setOrientation(bool isFacingRight) { facingRight = isFacingRight; }

void EntityState::setPosition(const sf::Vector2f &p) { position = p; }

// Methods
void EntityState::render(float deltaTime, sf::RenderWindow *window)
{
    animationTimer += deltaTime;
    if (animationTimer >= animationChangeInterval && !entityTextures.empty())
    {
        currentTextureIndex = (currentTextureIndex + 1) % entityTextures.size();
        entitySprite.setTexture(*entityTextures[currentTextureIndex]);
        entitySprite.setPosition(position);
        animationTimer = 0.0f;
    }
    entitySprite.setRotation(rotation);
    if (facingRight)
    {
        entitySprite.setScale(1.f, 1.f);
    }
    else
    {
        entitySprite.setScale(-1.f, 1.f);
    }
    window->draw(entitySprite);
}

void EntityState::addImg(const std::string &imagePath)
{
    auto texture = TextureCache::getInstance().getTexture(imagePath);
    entityTextures.push_back(texture);
    if (entityTextures.size() == 1)
    {
        entitySprite.setTexture(*entityTextures[0]);
        entitySprite.setPosition(position);
        this->setOriginCenter();
    }
}

void EntityState::setGlobalPosition(const sf::Vector2f &p)
{
    this->setPosition(p);
    entitySprite.setPosition(p);
}

void EntityState::setOriginCenter()
{
    sf::FloatRect bounds = entitySprite.getLocalBounds();
    entitySprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void EntityState::setTextures(const std::string &entityName, const std::string &state)
{
    entityTextures.clear();
    const std::string extensionName = ".png";
    for (int i = 0; i < texturesNumber; i++)
    {
        const std::string iToString = std::to_string(i);
        const std::string texturePath = "../assets/images/" + entityName + "_" + state + "_" + iToString + extensionName;
        this->addImg(texturePath);
    }
}

void EntityState::copyFrom(const EntityState &other)
{
    if (&other != nullptr)
    {
        this->currentTextureIndex = other.currentTextureIndex;
        this->animationTimer = other.animationTimer;
        this->entitySprite = other.entitySprite;
    }
}