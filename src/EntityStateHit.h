#ifndef ENTITY_STATE_HIT_H
#define ENTITY_STATE_HIT_H

#include <SFML/Graphics.hpp>
#include "EntityState.h"

class EntityStateHit : public EntityState
{
private:
public:
    EntityStateHit(const std::string &entityName);
};

#endif // ENTITY_STATE_HIT_H