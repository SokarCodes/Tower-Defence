#include "gameEntity.h"
#include "enemyEntity.h"
#include <iostream>
#include <string>
using namespace std;

enemyEntity::enemyEntity() : 
entityName_("Enemy")
{
    cout << this->name() << ": Entity created" << endl;
}    

enemyEntity::~enemyEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
}

void enemyEntity::update() {
    cout << this->name() << ": Entity running!" << endl;
}

std::string enemyEntity::name() {
    return entityName_;
}
