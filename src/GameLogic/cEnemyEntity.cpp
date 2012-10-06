/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>

#include <SFML/System.hpp>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include "entityEnums.h"

namespace gamelogic {

//cEnemyEntity::cEnemyEntity(entityInitType type, sf::Vector3f position) :
//    entityName_(""),
//    movespeed_(0),
//    type_(type),
//    state_(ALIVE)
//{
//    hitpoints_ = 100000;
//    position_ = position;
//}

cEnemyEntity::cEnemyEntity() :
    entityName_(""),
    movespeed_(0),
    type_(WALKING_ENEMY),
    state_(ALIVE)
{
    hitpoints_ = 100000;
    position_ = sf::Vector3f(0,0,0);
}

void cEnemyEntity::initializeEntity(entityInitType type, sf::Vector3f position)
{
    position_ = position;
    type_ = type;
    hitpoints_ = 100000;
    state_ = ALIVE;
    position_.z = -20;
    switch(type_)
    {
    case WALKING_ENEMY:
        entityName_ = "Walking_enemy";
        movespeed_ = 0;
        break;
    case FLYING_ENEMY:
        entityName_ = "Flying_enemy";
        movespeed_ = 0;
        break;
    case INVISIBLE_ENEMY:
        entityName_ = "Invisible_enemy";
        movespeed_ = 0;
        break;
    case FAST_ENEMY:
        entityName_ = "Fast_enemy";
        movespeed_ = 0;
        break;
    default:
        std::cout << "WARNING: initialize entity failed. No valid type acquired!\n";
    }
}

cEnemyEntity::~cEnemyEntity()
{
}

void cEnemyEntity::update(float frametime)
{
    // When enemy hitpoints are drained out, enemy is set to DECAY-state.
    // When in DECAY-state towers stop actions towards this enemy. DECAY-state
    // is kept for one frame and after that entity is put to DEAD-state and removed.
    // This guarantees that rendering layer renders last lethal shot to enemy.
    if (state_ == DEAD)
    {
        getMapper()->deleteEntity(this,type_);
        return;
    }
    else if (state_ == DECAYING)
    {
        state_ = DEAD;
    }
    else if (state_ == ALIVE)
    {
        int random = sf::Randomizer::Random(0,3);

        switch(random)
        {
        case 0:
            if(position_.x > movespeed_)
                position_.x -= movespeed_;
            break;
        case 1:
            if(position_.x < 779)
                position_.x += movespeed_;
            break;
        case 2:
            if (position_.y > movespeed_)
                position_.y -= movespeed_;
            break;
        case 3:
            if (position_.y < 579)
                position_.y += movespeed_;
            break;
        }

        // For now, only thing enemyEntity can do is die away.
        if (hitpoints_ <= 0)
            state_ = DECAYING;
    }
}

enemyState cEnemyEntity::getState() const
{
    return state_;
}

std::string cEnemyEntity::name() const
{
    return entityName_;
}
} // namespace gamelogic
