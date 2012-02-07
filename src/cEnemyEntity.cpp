#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include <iostream>
#include <string>
using namespace std;

cEnemyEntity::cEnemyEntity() :
entityName_("Enemy")    // Hardcoded for now to distinquish tower and enemy entities with name
{
    cout << this->name() << ": Entity constructor!" << " --> ";
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
