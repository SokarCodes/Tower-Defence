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
        movespeed_ = 200;
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
    direction_= normalize(direction_);

    entityName_ = "Projectile";

}

void cProjectile::update(float frametime)
{
    if (!lastMoveTime_)
        lastMoveTime_ = frametime;
    float step = frametime - lastMoveTime_;
    sf::Vector2f targetPos = target_->getPosition();

    switch (type_)
    {
    case HOMING:
        if (!getMapper()->entityExists(target_))
        {
            position_ += direction_ * (movespeed_ * step);
            lastMoveTime_ = frametime;

            // Projectile out of screen.
            if (position_.x < 0 || position_.y < 0)
                getMapper()->deleteEntity(this);
            else if (position_.x > 800 || position_.y > 600)
                getMapper()->deleteEntity(this);

            return;
        }
        direction_ = targetPos - position_;
        direction_ = normalize(direction_);

        if (distance(position_, targetPos) < (movespeed_ * step))
            position_ = targetPos;
        else
            position_ += direction_ * (movespeed_ * step);
        lastMoveTime_ = frametime;
        if (std::abs(position_.x - targetPos.x) < 5 && std::abs(position_.y - targetPos.y) < 5)
        {
            target_->inflictDamage(10);
            getMapper()->deleteEntity(this);
        }
        break;
    case INSTANT:
        if (distance(position_, targetPos) < (movespeed_ * step))
            position_ = targetPos;
        else
            position_ += direction_ * (movespeed_ * step);
        lastMoveTime_ = frametime;
        if (std::abs(position_.x - targetPos.x) < 5 && std::abs(position_.y - targetPos.y) < 5)
        {
            target_->inflictDamage(10);
            getMapper()->deleteEntity(this);
        }
        break;
    case INDIRECT:
        if (distance(position_, targetLocation_) < (movespeed_ * step))
            position_ = targetLocation_;
        else
        {
            // This is just acceleration test code: s = vt + at²/2
            float step = frametime - lastMoveTime_;
            double acceleration = 0.5*1*pow(step,2);
            double velocity = (movespeed_ * step) + acceleration;
            movespeed_ += (float)velocity;
            position_ += direction_ * (movespeed_ * step);
        }
        lastMoveTime_ = frametime;
        if (std::abs(position_.x - targetLocation_.x) < 3 && std::abs(position_.y - targetLocation_.y) < 3)
        {
            cMapper *instance = getMapper();
            switch(splash_)
            {
            case NO_SPLASH:
                instance->dealAOEDamage(position_, 1, 100);
                break;
            case LITTLE_SPLASH:
                instance->dealAOEDamage(position_, 50, 100);
                break;
            case HUGE_SPLASH:
                instance->dealAOEDamage(position_, 100, 100);
                break;
            case AWESOME_SPLASH:
                instance->dealAOEDamage(position_, 150, 100);
                break;
            default:
                std::cout << "No valid AOE splash specifier.\n";
                instance->dealAOEDamage(position_, 1, 100);
                break;
            }
            getMapper()->deleteEntity(this);
        }
        break;
    }
}

std::string cProjectile::name()
{
    return entityName_;
}

sf::Vector2f cProjectile::normalize(sf::Vector2f vector)
{
    // Calculate magnitude
    double magnitude = sqrt(vector.x*vector.x + vector.y*vector.y);
    sf::Vector2f normalized;
    normalized.x = vector.x / magnitude;
    normalized.y = vector.y / magnitude;
    return normalized;
}

double cProjectile::distance(sf::Vector2f A, sf::Vector2f B)
{
    sf::Vector2f diff = B-A;
    double distance = sqrt(pow(diff.x,2)+pow(diff.y,2));
    return distance;
}

double cProjectile::dotProduct(sf::Vector2f vector1, sf::Vector2f vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

}
