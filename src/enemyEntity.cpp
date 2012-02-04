#include "gameEntity.h"
#include "enemyEntity.h"
#include "cMapper.h"
#include <iostream>
#include <string>
using namespace std;

enemyEntity::enemyEntity() :
entityName_("Enemy")    // Hardcoded for now to distinquish tower and enemy entities with name
{
    cout << this->name() << ": Entity constructor!" << " --> ";
}    

enemyEntity::~enemyEntity()
{
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    getMapper()->deleteInstance(this);
}

void enemyEntity::update(float frametime)
{
    cout << this->name() << ": Entity running! Frametime: " << frametime << endl;
}

std::string enemyEntity::name()
{
    return entityName_;
}
