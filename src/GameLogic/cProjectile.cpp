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
    entityName_("Projectile"),
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
    std::cout << this->name() << ": Entity destruction!" << " --> ";
}

void cProjectile::initializeEntity()
{
    entityName_ = "Projectile";
    movespeed_ = 450;
    std::cout << "Projectile direction vector: " << direction_.x << "i " << direction_.y << "j with movespeed: " << movespeed_ << ".\n";
}

void cProjectile::update(float frametime)
{
    if (!lastMoveTime_)
        lastMoveTime_ = frametime;
    if (!getMapper()->entityExists(target_))
        getMapper()->deleteEntity(this);

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
    //else if (position_.x > 800 || position_.y > 600)
    //    getMapper()->deleteEntity(this);
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
