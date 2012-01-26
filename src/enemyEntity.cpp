#include "gameEntity.h"
#include "enemyEntity.h"
#include <iostream>
#include <string>
using namespace std;

enemyEntity::enemyEntity() : 
entityName("Enemy")
{
    cout << "Enemy entity created" << endl;
}    

enemyEntity::~enemyEntity() {
    std::cout << "enemyEntity destruction!" << "\n";
}

void enemyEntity::update() {
    cout << "Enemy entity running!" << endl;
}

std::string enemyEntity::name() {
    return entityName;
}