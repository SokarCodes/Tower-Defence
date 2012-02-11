#include <iostream>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"
#include "entityEnums.h"

namespace gamelogic {

cTowerEntity::cTowerEntity(towerType type, int x_coord, int y_coord) :
    enemy_(0),
    damage_(0),
    range_(0),
    reloadTimeout_(0),
    lastShotTime_(0),
    entityName_(""),
    type_(type)
{
    hitpoints_ = 100;
    x_coord_ = x_coord;
    y_coord_ = y_coord;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}

void cTowerEntity::initializeEntity()
{
    switch(type_)
    {
    case MORTAR_TOWER:
        damage_ = 20;
        range_ = 120;
        reloadTimeout_ = 2;
        entityName_ = "Mortar_tower";
        break;
    case ARROW_TOWER:
        damage_ = 10;
        range_ = 170;
        reloadTimeout_ = 1;
        entityName_ = "Arrow_tower";
        break;
    }
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
