#include <iostream>

#include "gameEntity.h"
#include "enemyEntity.h"
#include "towerEntity.h"

 
towerEntity::towerEntity() :
enemy(0),
damage(0),
range(0),
entityName("Tower")
{
    std::cout << "TowerEntity constructor!" << "\n";
}       

towerEntity::~towerEntity() {
    std::cout << "TowerEntity destruction!" << "\n";
}

void towerEntity::update() {
    if (enemy)
        fire();
    else
    {
        std::cout << "Need to acquire target!" << "\n";
        acquireTarget();
    }
}
void towerEntity::fire() {
    std::cout << "FIRE IN THE HOLE!" << "\n";
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
    std::cout << "Acquiring target!" << "\n";
}

std::string towerEntity::name() {
    return entityName;
}
