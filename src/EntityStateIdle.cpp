#include "EntityStateIdle.h"
#include "Ennemy.h"
#include "EnnemySoldier.h"

// Constructor
EntityStateIdle::EntityStateIdle(const std::string &entityName)
{
    this->setTextures(entityName, "idle");
}
