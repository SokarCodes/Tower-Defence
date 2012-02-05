#include <iostream>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"

 
cTowerEntity::cTowerEntity() :
enemy_(0),
damage_(0),
range_(0),
reloadTimeout_(-2),
entityName_("Tower")
{
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}       

cTowerEntity::~cTowerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    getMapper()->deleteInstance(this);
}

void cTowerEntity::update(float frametime) {
    //std::cout << this->name() << ": Frametime  " << frametime << "\n";
    if (enemy_)
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
void cTowerEntity::fire() {
    std::cout << this->name() <<  ": FIRE IN THE HOLE!" << "\n";
}

void cTowerEntity::setDamage(const unsigned int damage) {
    damage_ = damage;
}

void cTowerEntity::setRange(const unsigned int range) {
    range_ = range;
}

void cTowerEntity::setTarget(cGameEntity *enemy) {
    enemy_ = enemy;
}

void cTowerEntity::acquireTarget() {
    std::cout << this->name() << ": Acquiring target!" << "\n";
    enemy_ = getMapper()->getTarget();
}

std::string cTowerEntity::name() {
    return entityName_;
}
