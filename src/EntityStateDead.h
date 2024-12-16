#ifndef ENTITY_STATE_DEAD_H
#define ENTITY_STATE_DEAD_H

#include <SFML/Graphics.hpp>
#include "EntityState.h"

class EntityStateDead : public EntityState
{
private:
public:
    EntityStateDead(const std::string &entityName);
};

#endif // ENTITY_STATE_DEAD_H