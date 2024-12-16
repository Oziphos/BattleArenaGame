#ifndef ENTITY_STATE_ATTACK_H
#define ENTITY_STATE_ATTACK_H

#include <SFML/Graphics.hpp>
#include "EntityState.h"

class EntityStateAttack : public EntityState
{
private:
public:
    EntityStateAttack(const std::string &entityName);
};

#endif // ENTITY_STATE_ATTACK_H