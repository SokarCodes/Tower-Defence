#include <iostream>

#include <SFML/System.hpp>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"

namespace gamelogic {

cEnemyEntity::cEnemyEntity(int x, int y) :
    entityName_("Enemy"),   // Hardcoded for now to distinquish tower and enemy entities with name
    movespeed_(5)
{
    hitpoints_ = 100;
    x_coord_ = x;
    y_coord_ = y;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}    

cEnemyEntity::~cEnemyEntity()
{
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    //getMapper()->deleteEntity(this);
}

void cEnemyEntity::update(float frametime)
{
    int random = sf::Randomizer::Random(0,3);

    switch(random)
    {
    case 0:
        if(x_coord_ > movespeed_)
            x_coord_ -= movespeed_;
        break;
    case 1:
        if(x_coord_ < 779)
            x_coord_ += movespeed_;
        break;
    case 2:
        if (y_coord_ > movespeed_)
            y_coord_ -= movespeed_;
        break;
    case 3:
        if (y_coord_ < 579)
            y_coord_ += movespeed_;
        break;
    }

    // For now, only thing enemyEntity can do is die away.
    if (hitpoints_ <= 0)
        getMapper()->deleteEntity(this);
}

std::string cEnemyEntity::name()
{
    return entityName_;
}
} // namespace gamelogic
