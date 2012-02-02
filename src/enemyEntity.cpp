#include "gameEntity.h"
#include "enemyEntity.h"
#include "cMapper.h"
#include <iostream>
#include <string>
using namespace std;

enemyEntity::enemyEntity(cMapper *mapper) :
entityName_("Enemy"),
mapper_(mapper)
{
    cout << this->name() << ": Entity constructor!" << " --> ";
}    

enemyEntity::~enemyEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    mapper_->deleteInstance(this);
}

void enemyEntity::update() {
    cout << this->name() << ": Entity running!" << endl;
}

std::string enemyEntity::name() {
    return entityName_;
}
