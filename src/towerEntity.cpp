#include <iostream>

#include "gameEntity.h"
#include "enemyEntity.h"
#include "towerEntity.h"
#include "cMapper.h"

 
towerEntity::towerEntity(cMapper* mapper) :
enemy(0),
damage(0),
range(0),
entityName("Tower"),
mapper_(mapper)
{
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}       

towerEntity::~towerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
}

void towerEntity::update() {
    if (enemy)
        fire();
    else
    {
        std::cout << this->name() << ": Need to acquire target!" << "\n";
        acquireTarget();
    }
}
void towerEntity::fire() {
    std::cout << this->name() <<  ": FIRE IN THE HOLE!" << "\n";
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
    std::cout << this->name() << ": Acquiring target!" << "\n";
    enemy = mapper_->getTarget();
}

std::string towerEntity::name() {
    return entityName;
}
