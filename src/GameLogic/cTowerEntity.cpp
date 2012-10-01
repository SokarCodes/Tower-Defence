/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cTowerEntity.h"
#include "cMapper.h"
#include "entityEnums.h"
#include "cProjectile.h"

namespace gamelogic {

//cTowerEntity::cTowerEntity(entityInitType type, sf::Vector3f position) :
//    enemy_(0),
//    range_(0),
//    reloadTimeout_(0),
//    lastShotTime_(0),
//    entityName_(""),
//    type_(type),
//    lifetime_(15)
//{
//    hitpoints_ = 100;
//    position_ = position;
//}

cTowerEntity::cTowerEntity() :
    enemy_(0),
    range_(0),
    reloadTimeout_(0),
    lastShotTime_(0),
    entityName_(""),
    type_(MORTAR_TOWER),
    lifetime_(15)
{
    hitpoints_ = 1;
    position_ = sf::Vector3f(0,0,0);
}

void cTowerEntity::initializeEntity(entityInitType type, sf::Vector3f position)
{
    type_ = type;
    position_ = position;
    switch(type_)
    {
    case MORTAR_TOWER:
        range_ = 300;
        reloadTimeout_ = 1;
        entityName_ = "Mortar_tower";
        break;
    case ARROW_TOWER:
        range_ = 300;
        reloadTimeout_ = 1;
        entityName_ = "Arrow_tower";
        break;
    case ICE_TOWER:
        range_ = 350;
        reloadTimeout_ = 1;
        entityName_ = "Ice_tower";
        break;
    case SPECIAL_TOWER:
        range_ = 500;
        reloadTimeout_ = 3;
        entityName_ = "Special_tower";
        break;
    default:
        std::cout << "WARNING: initialize entity failed. No valid type acquired!\n";

    }
}

cTowerEntity::~cTowerEntity() {
}

void cTowerEntity::update(float frametime)
{
    if (enemy_ && enemy_->getState() == ALIVE)
    {
        if (isInRange())
        {
            if ( (frametime - lastShotTime_) >= reloadTimeout_ )
            {
                lastShotTime_ = frametime;
                fire();
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
    if ((frametime - lastShotTime_) > lifetime_ && lastShotTime_ != 0)
        getMapper()->deleteEntity(this, type_);
}
void cTowerEntity::fire() {
    // Tower generates new projectile which does the damage if hit.
    // Tower does not care about anything else but calculating distance and launching projectile.
    getMapper()->addProjectile(this, enemy_);
}

void cTowerEntity::setRange(const unsigned int range) {
    range_ = range;
}

void cTowerEntity::acquireTarget() {
    enemy_ = getMapper()->getTarget(position_, range_);
}

bool cTowerEntity::isInRange()
{
    float g = 50.f;
    float movespeed = 100.f;
    sf::Vector3f targetLocation_ = enemy_->getPosition();
    float v2 = pow(movespeed,2);
    float v4 = pow(v2,2);
    float x = distance(position_,targetLocation_);
    float y = (targetLocation_.z - position_.z);
    float D = v4 - g*(g*x*x+2.f*y*v2);
    if (D < 0)
        return false;
    else
        return true;
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
    return enemy_->getState() == ALIVE ? true : false;
}

double cTowerEntity::distance(sf::Vector3f A, sf::Vector3f B)
{
    sf::Vector3f diff = A-B;
    double distance = sqrt(pow(diff.x,2) + pow(diff.y,2) + pow(diff.z,2));
    return distance;
}

} // namespace gamelogic
