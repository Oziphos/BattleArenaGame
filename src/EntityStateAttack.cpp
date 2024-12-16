#include "EntityStateAttack.h"

// Constructor
EntityStateAttack::EntityStateAttack(const std::string &entityName)
{
    this->setTextures(entityName, "attack");
}
