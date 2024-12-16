#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Entity;

class EntityState
{
private:
    std::vector<std::shared_ptr<sf::Texture>> entityTextures;
    sf::Sprite entitySprite;
    float rotation;
    bool facingRight;
    std::size_t currentTextureIndex = 0;
    float animationTimer = 0.0f;
    float animationChangeInterval = 0.14f;
    int texturesNumber = 12;
    sf::Vector2f position;

public:
    // Constructors
    EntityState() = default;
    ~EntityState() = default;
    // Getters
    const std::vector<std::shared_ptr<sf::Texture>> &getTextures() const;
    sf::Sprite getSprite() const;
    float getRotation() const;
    bool getOrientation() const;
    std::size_t getCurrentTextureIndex() const;
    float getAnimationTimer() const;
    float getAnimationChangeInterval() const;
    sf::Vector2f getPosition() const;
    // Setters
    void setTextures(std::vector<std::shared_ptr<sf::Texture>> &&t);
    void setSprite(const sf::Sprite &s);
    void setRotation(const float &r);
    void setOrientation(bool facingRight);
    void setCurrrentTextureIndex(const std::size_t &i);
    void setAnimationTimer(const float &at);
    void setAnimationChangeInterval(const float &ai);
    void setPosition(const sf::Vector2f &p);
    // Methods
    void setGlobalPosition(const sf::Vector2f &p);
    void render(float deltaTime, sf::RenderWindow *w);
    void addImg(const std::string &imgPath);
    void setTextures(const std::string &entityName, const std::string &state);
    void copyFrom(const EntityState &other);
    void setOriginCenter();
};

#endif // ENTITY_STATE_H