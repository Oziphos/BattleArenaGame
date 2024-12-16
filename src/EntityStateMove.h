#ifndef ENTITY_STATE_MOVE_H
#define ENTITY_STATE_MOVE_H

#include <SFML/Graphics.hpp>
#include "EntityState.h"

class EntityStateMove : public EntityState
{
private:
public:
    EntityStateMove(const std::string &entityName);
};

#endif // ENTITY_STATE_MOVE_H