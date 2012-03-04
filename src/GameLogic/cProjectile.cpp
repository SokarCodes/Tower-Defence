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
    target_(target),
    targetLocation_(0,0),
    splash_(NO_SPLASH)
{
}

cProjectile::~cProjectile()
{
    std::cout << entityName_ << ": Entity destruction!" << " --> ";
}

void cProjectile::initializeEntity()
{
    switch (owner_->getType())
    {
    case MORTAR_TOWER:
        type_ = INDIRECT;
        splash_ = HUGE_SPLASH;
        movespeed_ = 300;
        targetLocation_ = target_->getPosition();
        break;
    case ARROW_TOWER:
        type_ = HOMING;
        splash_ = NO_SPLASH;
        movespeed_ = 450;
        break;
    case ICE_TOWER:
        type_ = HOMING;
        splash_ = NO_SPLASH;
        movespeed_ = 450;
        break;
    case SPECIAL_TOWER:
        type_ = INSTANT;
        splash_ = LITTLE_SPLASH;
        movespeed_ = 9999;
        break;
    default:
        type_ = INDIRECT;
        splash_ = HUGE_SPLASH;
        movespeed_ = 300;
        std::cout << "No valid type given. Using INDIRECT projectile type.\n";
    }

    // Set some obsolete name for this entity.
    entityName_ = "Projectile";

    // Get position from tower launching this projectile.
    position_ = owner_->getPosition();

    // Get direction vector between target and position.
    direction_ = target_->getPosition() - position_;

    // Normalize direction to unit vector.
    normalize(direction_);

    entityName_ = "Projectile";

}

void cProjectile::update(float frametime)
{
    if (!lastMoveTime_)
        lastMoveTime_ = frametime;

    switch (type_)
    {
    case HOMING:
        if (!getMapper()->entityExists(target_))
        {
            position_ += direction_ * ((float)movespeed_ * (frametime - lastMoveTime_));
            lastMoveTime_ = frametime;

            // Projectile out of screen.
            if (position_.x < 0 || position_.y < 0)
                getMapper()->deleteEntity(this);
            else if (position_.x > 800 || position_.y > 600)
                getMapper()->deleteEntity(this);

            return;
        }

        direction_ = target_->getPosition() - position_;
        normalize(direction_);

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
        break;
    case INSTANT:
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
        break;
    case INDIRECT:
        if (distance(position_, targetLocation_) < ((float)movespeed_ * (frametime - lastMoveTime_)))
            position_ = targetLocation_;
        else
            position_ += direction_ * ((float)movespeed_ * (frametime - lastMoveTime_));
        lastMoveTime_ = frametime;
        if (std::abs(position_.x - targetLocation_.x) < 3 && std::abs(position_.y - targetLocation_.y) < 3)
        {
            cMapper *instance = getMapper();
            instance->dealAOEDamage(position_, 50, 100);
            getMapper()->deleteEntity(this);
        }
        break;
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
