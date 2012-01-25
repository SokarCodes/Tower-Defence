#include "gameEntity.h"
#include "enemyEntity.h"
#include <iostream>
using namespace std;

enemyEntity::enemyEntity() {
    cout << "Enemy entity created" << endl;
}    

enemyEntity::~enemyEntity() {
    std::cout << "enemyEntity destruction!" << std::endl;
}

void enemyEntity::update() {
    cout << "Enemy entity running!" << endl;
}
