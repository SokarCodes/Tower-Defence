#include <iostream>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"

 
cTowerEntity::cTowerEntity(int x, int y) :
enemy_(0),
damage_(0),
range_(10),
reloadTimeout_(2),
lastShotTime_(0.f),
entityName_("Tower")
{
    x_coord_ = x;
    y_coord_ = y;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}       

cTowerEntity::~cTowerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    getMapper()->deleteInstance(this);
}

void cTowerEntity::update(float frametime) {
    if (enemy_)
    {
        if ( (frametime - lastShotTime_) >= reloadTimeout_ )
        {
            lastShotTime_ = frametime;
            fire();
            std::cout << ". frametime: " << frametime << ".\n" <<this->name() << ": Reloading!\n";
        }
    }
    else
    {
        acquireTarget();
    }
}
void cTowerEntity::fire() {
    std::cout << this->name() <<  ": FIRE IN THE HOLE!";
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
    enemy_ = getMapper()->getTarget(x_coord_, y_coord_, range_);
}

std::string cTowerEntity::name() {
    return entityName_;
}
