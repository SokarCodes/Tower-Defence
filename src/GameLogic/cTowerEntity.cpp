#include <iostream>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"
#include "towerEnums.h"

namespace gamelogic {

cTowerEntity::cTowerEntity(int x, int y) :
    enemy_(0),
    damage_(20),
    range_(200),
    reloadTimeout_(2),
    lastShotTime_(0.f),
    entityName_("Tower")
{
    hitpoints_ = 10;
    x_coord_ = x;
    y_coord_ = y;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}       

cTowerEntity::~cTowerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
}

void cTowerEntity::update(float frametime) {
    if (enemy_ && getMapper()->entityExists(enemy_) && getMapper()->isInRange(enemy_, this))
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
        enemy_ = 0;
        acquireTarget();
    }
}
void cTowerEntity::fire() {
    enemy_->inflictDamage(damage_);
    std::cout << this->name() <<  ": FIRE IN THE HOLE!";
}

void cTowerEntity::setDamage(const unsigned int damage) {
    damage_ = damage;
}

void cTowerEntity::setRange(const unsigned int range) {
    range_ = range;
}

void cTowerEntity::acquireTarget() {
    enemy_ = getMapper()->getTarget(x_coord_, y_coord_, range_);
}

std::string cTowerEntity::name() {
    return entityName_;
}

int cTowerEntity::getRange()
{
    return range_;
}

} // namespace gamelogic
