#include "cGameEntity.h"

// mapper_ definition
cMapper* cGameEntity::mapper_ = cMapper::getInstance();

void cGameEntity::inflictDamage(int dmg)
{
    this->hitpoints_ -= dmg;
}
