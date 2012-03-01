/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include "cProjectile.h"
#include "cTowerEntity.h"
#include <cmath>

namespace gamelogic {

cProjectile::cProjectile(cGameEntity *owner, cGameEntity *target) :
    entityName_(""),
    movespeed_(0),
    lastMoveTime_(0),
    owner_(owner),
    target_(target)

{
    position_ = owner_->getPosition();
    direction_ = target_->getPosition() - position_;
    normalize(direction_);
}

cProjectile::~cProjectile()
{

}

void cProjectile::initializeEntity()
{
    entityName_ = "Projectile";
    movespeed_ = 50;
    std::cout << "Projectile direction vector: " << direction_.x << "i " << direction_.y << "j with movespeed: " << movespeed_ << ".\n";
}

void cProjectile::update(float frametime)
{
    if (!lastMoveTime_)
        lastMoveTime_ = frametime;

    if (frametime - lastMoveTime_ > 1)
        getMapper()->deleteEntity(this);
}

std::string cProjectile::name()
{
    return entityName_;
}

void cProjectile::normalize(sf::Vector2f vector)
{
    // Calculate magnitude
    double magnitude = sqrt(vector.x*vector.x + vector.y*vector.y);
    sf::Vector2f normalized;
    normalized.x = vector.x / magnitude;
    normalized.y = vector.y / magnitude;
    direction_ = normalized;
}

}
