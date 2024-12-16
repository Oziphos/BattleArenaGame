#include "EntityStateHit.h"

// Constructor
EntityStateHit::EntityStateHit(const std::string &entityName)
{
    this->setTextures(entityName, "hit");
}
