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
}

cProjectile::~cProjectile()
{

}

void cProjectile::initializeEntity()
{
    entityName_ = "Projectile";
    movespeed_ = 50;
}

void cProjectile::update(float frametime)
{

}

std::string cProjectile::name()
{
    return entityName_;
}

}
