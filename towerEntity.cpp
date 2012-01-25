#include <iostream>

#include "gameEntity.h"
#include "enemyEntity.h"
#include "towerEntity.h"
 
towerEntity::towerEntity() :
damage(0),
range(0),
enemy(0)
{
    std::cout << "Hello from towerEntity constructor!" << std::endl;
}       

towerEntity::~towerEntity() {
    std::cout << "Lol form towerEntity destructor!" << std::endl;
}

void towerEntity::update() {
    if (enemy)
        fire();
    else
    {
        std::cout << "Need to acquire target!" << std::endl;
        acquireTarget();
    }
}
void towerEntity::fire() {
    std::cout << "FIRE IN THE HOLE!" << std::endl;
}

void towerEntity::setDamage(const unsigned int dmg) {
    damage = dmg;
}

void towerEntity::setRange(const unsigned int rng) {
    range = rng;
}

void towerEntity::setTarget(gameEntity *newEnemy) {
    enemy = newEnemy;
}

void towerEntity::acquireTarget() {
    std::cout << "Acquiring target!" << std::endl;
}