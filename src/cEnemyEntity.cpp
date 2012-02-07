#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include <iostream>
#include <string>
using namespace std;

cEnemyEntity::cEnemyEntity(int x, int y) :
entityName_("Enemy")    // Hardcoded for now to distinquish tower and enemy entities with name
{
    hitpoints_ = 10000;
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
    // For now, only thing enemyEntity can do is die away.
    if (hitpoints_ <= 0)
        getMapper()->deleteEntity(this);
}

std::string cEnemyEntity::name()
{
    return entityName_;
}
