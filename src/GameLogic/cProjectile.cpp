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
}

cProjectile::~cProjectile()
{
    std::cout << entityName_ << ": Entity destruction!" << " --> ";
}

void cProjectile::initializeEntity()
{
    // Set some obsolete name for this entity.
    entityName_ = "Projectile";

    // Get position from tower launching this projectile.
    position_ = owner_->getPosition();

    // Get direction vector between target and position.
    direction_ = target_->getPosition() - position_;

    // Normalize direction to unit vector.
        normalize(direction_);

    entityName_ = "Projectile";
    movespeed_ = 450;
}

void cProjectile::update(float frametime)
{
    if (!lastMoveTime_)
        lastMoveTime_ = frametime;
    if (!getMapper()->entityExists(target_))
    {
        position_ += direction_ * ((float)movespeed_ * (frametime - lastMoveTime_));
        lastMoveTime_ = frametime;
        if (position_.x < 0 || position_.y < 0)
            getMapper()->deleteEntity(this);
        else if (position_.x > 800 || position_.y > 600)
            getMapper()->deleteEntity(this);
        return;
    }

//    direction_ = target_->getPosition() - position_;
//    normalize(direction_);

    if (distance(position_, target_->getPosition()) < ((float)movespeed_ * (frametime - lastMoveTime_)))
        position_ = target_->getPosition();
    else
        position_ += direction_ * ((float)movespeed_ * (frametime - lastMoveTime_));
    lastMoveTime_ = frametime;
    if (std::abs(position_.x - target_->getPosition().x) < 5 && std::abs(position_.y - target_->getPosition().y) < 5)
    {
        target_->inflictDamage(10);
        getMapper()->deleteEntity(this);
    }
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

double cProjectile::distance(sf::Vector2f A, sf::Vector2f B)
{
    sf::Vector2f diff = B-A;
    double distance = sqrt(pow(diff.x,2)+pow(diff.y,2));
    return distance;
}

}
