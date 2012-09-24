/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include "cProjectile.h"
#include "cTowerEntity.h"
#include "entityEnums.h"
#include <cmath>
#define PI 3.1415

namespace gamelogic {

//cProjectile::cProjectile(cGameEntity *owner, cGameEntity *target) :
//    entityName_(""),
//    movespeed_(0),
//    lastUpdateTime_(0),
//    owner_(owner),
//    target_(target),
//    targetLocation_(0,0,0),
//    direction_(0,0,0),
//    acceleration_(0,0,-200.f),
//    velocity_(0,0,0),
//    splash_(NO_SPLASH)
//{
//}

cProjectile::cProjectile() :
    entityName_(""),
    movespeed_(0),
    lastUpdateTime_(0),
    owner_(0),
    target_(0),
    targetLocation_(0,0,0),
    direction_(0,0,0),
    acceleration_(0,0,-200.f),
    velocity_(0,0,0),
    splash_(NO_SPLASH)
{
}


cProjectile::~cProjectile()
{
}

void cProjectile::initializeEntity(entityInitType type, sf::Vector3f position)
{
    lastUpdateTime_ = 0;
    type_ = type;
    position_ = position;
    float g = 50.f;
    movespeed_ = 100.f;
    // Set some obsolete name for this entity.
    entityName_ = "Projectile";

    // Get targetlocation
    targetLocation_ = target_->getPosition();

    // Calculate distance between these two points.
    double dist = distance(position_,targetLocation_);

    // Get direction vector between target and position. XY components.
    direction_ = normalize(targetLocation_ - position_);

    float v2 = pow(movespeed_,2);
    float v4 = pow(v2,2);
    float x = dist;
    float y = (targetLocation_.z - position_.z);
    float D = v4 - g*(g*x*x+2.f*y*v2);
    float angle1 = 0;
    float angle2 = 0;
    if (D >= 0)
    {
        angle1 = atan((v2 - sqrt(D))/(g*x));
        angle2 = atan((v2 + sqrt(D))/(g*x));
    }
    if (angle1 < 0.09)
    {
        angle1 = angle2;
    }

    // Set height angle
    direction_.z = sin(angle1);
    // Reset both of XY vectors according to new unitvector XYZ.
    direction_.x *= cos(angle1);
    direction_.y *= cos(angle1);

    // Velocity vector. This is added to position ever step.
    velocity_ = direction_ * movespeed_;

    // Acceleration. Make bullet drop in negative z-vector. This is added to velocity every step.
    acceleration_ = sf::Vector3f(0.f,0.f,-g);
}

void cProjectile::update(float frametime)
{
    if (!lastUpdateTime_)
        lastUpdateTime_ = frametime;

    // Calculate timestep
    float step = frametime - lastUpdateTime_;

    // Velocity change with possible acceleration.
    velocity_ += acceleration_*step;

    // Position is calculated with new velocity.
    position_ += velocity_ * step;
    //std::cout << "Position.Z: " << position_.z << ", VelocityZ: " << velocity_.z <<  ", AccelerationZ: " << acceleration_.z << "\n";

    // Update lastUpdateTime to correspond this frametime.
    lastUpdateTime_ = frametime;

    // Let projectile live until it hits the same level of Z as target entity.
    if (position_.z < targetLocation_.z)
    {
        getMapper()->dealAOEDamage(position_,15,100);
        getMapper()->deleteEntity(this, type_);
        return;
    }

}

std::string cProjectile::name()
{
    return entityName_;
}

sf::Vector3f cProjectile::normalize(sf::Vector3f vector)
{
    double magnitude = sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
    sf::Vector3f normalized;
    normalized.x = vector.x / magnitude;
    normalized.y = vector.y / magnitude;
    normalized.z = vector.z / magnitude;
    return normalized;
}

double cProjectile::distance(sf::Vector3f A, sf::Vector3f B)
{
    sf::Vector3f diff = A-B;
    double distance = sqrt(pow(diff.x,2) + pow(diff.y,2) + pow(diff.z,2));
    return distance;
}

double cProjectile::dotProduct(sf::Vector3f vector1, sf::Vector3f vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

}
