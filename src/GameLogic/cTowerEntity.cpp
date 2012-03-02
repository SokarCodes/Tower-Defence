/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"
#include "entityEnums.h"
#include "cProjectile.h"

namespace gamelogic {

cTowerEntity::cTowerEntity(towerType type, sf::Vector2f position) :
    enemy_(0),
    damage_(0),
    range_(0),
    reloadTimeout_(0),
    lastShotTime_(0),
    entityName_(""),
    type_(type),
    lifetime_(15)
{
    hitpoints_ = 100;
    position_ = position;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}

void cTowerEntity::initializeEntity()
{
    switch(type_)
    {
    case MORTAR_TOWER:
        damage_ = 20;
        range_ = 400;
        reloadTimeout_ = 0.2;
        entityName_ = "Mortar_tower";
        break;
    case ARROW_TOWER:
        damage_ = 10;
        range_ = 300;
        reloadTimeout_ = 1;
        entityName_ = "Arrow_tower";
        break;
    case ICE_TOWER:
        damage_ = 70;
        range_ = 350;
        reloadTimeout_ = 1;
        entityName_ = "Ice_tower";
        break;
    case SPECIAL_TOWER:
        damage_ = 30;
        range_ = 500;
        reloadTimeout_ = 3;
        entityName_ = "Special_tower";
        break;
    default:
        std::cout << "WARNING: initialize entity failed. No valid type acquired!\n";

    }
}

cTowerEntity::~cTowerEntity() {
    std::cout << this->name() << ": Entity destruction!" << " --> ";
}

void cTowerEntity::update(float frametime) {
    if (enemy_)
    {
        if (getMapper()->entityExists(enemy_))
        {
            if (getMapper()->isInRange(enemy_, this))
            {
                if ( (frametime - lastShotTime_) >= reloadTimeout_ && enemy_->getState() == ALIVE )
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
        else
        {
            enemy_ = 0;
            acquireTarget();
        }
    }
    else
    {
        acquireTarget();
    }
    if ((frametime - lastShotTime_) > lifetime_ && lastShotTime_ != 0)
        getMapper()->deleteEntity(this);
}
void cTowerEntity::fire() {
    // Tower generates new projectile which does the damage if hit.
    // Tower does not care about anything else but targeting and launching projectile.
    getMapper()->addProjectile(this, enemy_);
}

void cTowerEntity::setDamage(const unsigned int damage) {
    damage_ = damage;
}

void cTowerEntity::setRange(const unsigned int range) {
    range_ = range;
}

void cTowerEntity::acquireTarget() {
    enemy_ = getMapper()->getTarget(position_, range_);
}

std::string cTowerEntity::name() {
    return entityName_;
}

int cTowerEntity::getRange()
{
    return range_;
}

bool cTowerEntity::hasEnemy()
{
    return getMapper()->entityExists(enemy_);
}

} // namespace gamelogic
