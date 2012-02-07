#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include <iostream>
#include <string>
using namespace std;

cEnemyEntity::cEnemyEntity(int x, int y) :
entityName_("Enemy")    // Hardcoded for now to distinquish tower and enemy entities with name
{
    x_coord_ = x;
    y_coord_ = y;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}    

cEnemyEntity::~cEnemyEntity()
{
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    getMapper()->deleteInstance(this);
}

void cEnemyEntity::update(float frametime)
{
    //cout << this->name() << ": Entity running!\n";
}

std::string cEnemyEntity::name()
{
    return entityName_;
}
