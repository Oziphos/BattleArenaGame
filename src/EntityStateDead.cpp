#include "EntityStateDead.h"

// Constructor
EntityStateDead::EntityStateDead(const std::string &entityName)
{
    this->setTextures(entityName, "dead");
}
