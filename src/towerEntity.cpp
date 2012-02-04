#include <iostream>

#include "gameEntity.h"
#include "enemyEntity.h"
#include "towerEntity.h"
#include "cMapper.h"

 
towerEntity::towerEntity() :
enemy(0),
damage(0),
range(0),
reloadTimeout_(-2),
entityName("Tower")
{
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}       

towerEntity::~towerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    getMapper()->deleteInstance(this);
}

void towerEntity::update(float frametime) {
    //std::cout << this->name() << ": Frametime  " << frametime << "\n";
    if (enemy)
    {
        if((frametime - reloadTimeout_)<= 2)
            std::cout << "Reloading cannon!\n";
        else    
        {
            reloadTimeout_ = frametime;
            fire();
        }
    }
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
    enemy = getMapper()->getTarget();
}

std::string towerEntity::name() {
    return entityName;
}
