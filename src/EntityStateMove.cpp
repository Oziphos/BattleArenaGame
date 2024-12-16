#include "EntityStateMove.h"

// Constructor
EntityStateMove::EntityStateMove(const std::string &entityName)
{
    this->setTextures(entityName, "move");
}
