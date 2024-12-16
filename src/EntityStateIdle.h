#ifndef ENTITY_STATE_IDLE_H
#define ENTITY_STATE_IDLE_H

#include <SFML/Graphics.hpp>
#include "EntityState.h"

class EntityStateIdle : public EntityState
{
private:
public:
    EntityStateIdle(const std::string &entityName);
};

#endif // ENTITY_STATE_IDLE_H